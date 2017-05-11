#include"P3D_RenderScene.h"
#include"P3D_PathTracer.h"
P3D_DEFINE_SINGLETON(P3DRenderScene);

P3DRenderScene::~P3DRenderScene(){
	clear();
}

void P3DRenderScene::clear(){
	for (auto item : m_Objects){
		SAFERELEASE(item);
	}
	m_Objects.clear();
}

void P3DRenderScene::addObject(P3DRenderable* obj){
	if (obj == nullptr)
		return;
	m_Objects.push_back(obj);
}

bool P3DRenderScene::addModel(std::string &filename, bool kdTree){
	P3DLitModelRenderable*newModel = new P3DLitModelRenderable;
	if (!newModel){
		char msg[512];
		sprintf_s(msg, "error to create P3DLitModelRenderable : %s", filename.c_str());
		ERROROUT(msg);
		exit(1);
	}
	if (!newModel->LoadFromFile(filename, kdTree))
		return false;
	addObject(newModel);
}

bool P3DRenderScene::addSphereObj(glm::vec3 &center, float raduis,P3DMaterial &mat){
	P3DSphereRenderable *tmpSphere = new P3DSphereRenderable;
	if (tmpSphere == nullptr){
		ERROROUT("error to creat sphere");
		return false;
	}
	tmpSphere->Init(raduis,center,mat);
	addObject(tmpSphere);
		
}

void P3DRenderScene::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (auto item : m_Objects){
		if (item == nullptr)
			continue;
		item->Render();
	}
}
P3DObjIntersection P3DRenderScene::Intersect(P3DRay &ray){
	P3DObjIntersection ret_its = P3DObjIntersection();
	P3DObjIntersection tmp;
	for (auto item : m_Objects){
		P3DObjIntersection tmp;
		item->InterSect(ray, tmp, ret_its.m_Dis);
		if (tmp.m_IsHit)// && tmp.m_Dis < ret_its.m_Dis)
			ret_its = tmp;
	}
	return ret_its;
}

glm::vec3 P3DRenderScene::GoTrace(P3DRay &ray,int n_depth){

	P3DObjIntersection myInter =  Intersect(ray);
	if (!myInter.m_IsHit)
		return glm::vec3(0, 0, 0);
	P3DMaterial *tMat = myInter.m_Material;
	if (tMat->m_MaterialType == EMMI)
		return tMat->m_emission;
	//俄罗斯转盘 处理最大次数问题

	glm::vec3 T_Col = tMat->m_colour;
	float Col_Max = std::max(std::max(T_Col.r, T_Col.g), T_Col.b);
	if (n_depth >= P3DPahtTracer::Instance().GetMaxDepth()){
		if (Col_Max < P3DRandom::Instance().GetDouble())
			return T_Col;// tMat->m_colour;  //cuole 
		T_Col *= (1.0f / Col_Max);
	}
	//光线可能是在模型内部传递
	glm::vec3 orNormal = myInter.m_Vertex.normal;
	glm::vec3 corNormal = glm::dot(orNormal, ray.m_Dirction) < 0 ? orNormal : -1.0f * orNormal;
	//处理反射光线

	if (tMat->m_MaterialType == MaterialType::DIFF){  //为漫反射表面 随机生成光线

		float Theta = P3DRandom::Instance().GetDouble() * PI *2;
		float Tlen2 = P3DRandom::Instance().GetDouble();
		float Tlen = sqrtf(Tlen2);

		glm::vec3 x_axi = glm::normalize(glm::cross(glm::vec3(0, 1, 0), corNormal));
		glm::vec3 y_axi = glm::normalize(glm::cross(corNormal, x_axi));
		glm::vec3 t_dir = x_axi * cos(Theta) * Tlen + y_axi * sin(Theta) * Tlen + corNormal * sqrtf(1 - Tlen2);
		t_dir = glm::normalize(t_dir);
		P3DRay newRay(myInter.m_Vertex.pos, t_dir);
		return  T_Col * GoTrace(newRay, n_depth + 1);
	}  //如果是镜面反射
	if (tMat->m_MaterialType == MaterialType::SPEC){
		//计算反射光线
		glm::vec3 TDir = glm::reflect(-ray.m_Dirction, corNormal);
		P3DRay new_Ray(myInter.m_Vertex.pos, TDir);
		return  T_Col * GoTrace(new_Ray, n_depth + 1);
	}
	//那么就是折射 既有镜面反射又有透射

	glm::vec3 refdir = glm::reflect(-ray.m_Dirction, corNormal); //反射光线
	P3DRay refRay(myInter.m_Vertex.pos, refdir);
	float Trefra = glm::dot(corNormal, orNormal) > 0 ? 1.0f / tMat->m_Refra : tMat->m_Refra;  //可能实在模型内部
	float cosTheta = glm::dot(ray.m_Dirction, corNormal);  //其实是-cos
	if (1 - cosTheta * cosTheta > 1.0f/(Trefra * Trefra)){  //发生全反射

		return tMat->m_colour * GoTrace(refRay, n_depth + 1);
	}
	//计算折射光线
	//return glm::vec3(0, 0, 0);
	glm::vec3 refradir = glm::normalize(glm::refract(ray.m_Dirction, corNormal, 1.0f / Trefra));

	//使用菲涅耳公式计算 折射和反射的光线
	double f0 = (Trefra - 1)*(Trefra - 1) / ((Trefra + 1) * (Trefra + 1));
	double Pfre = f0 + (1 - f0) * pow(1 + cosTheta, 5);  //反射强度
	double pfra = 1.0 - Pfre;                            //折射强度
	float Tf = 0.25 + Pfre * 0.5f;     //俄罗斯转盘
	float AllRe = Pfre / Tf;
	float AllFra = pfra / (1 - Tf);
	P3DRay FraRay(myInter.m_Vertex.pos, refradir);
	if (n_depth <= 1){
		glm::vec3 col_re = (float)Pfre * GoTrace(refRay, n_depth + 1);
		glm::vec3 col_fra = (float)pfra * GoTrace(FraRay, n_depth + 1);
		return  tMat->m_colour *(col_re + col_fra);
	}
	if (P3DRandom::Instance().GetDouble() < Tf)
		return AllRe * tMat->m_colour * GoTrace(refRay, n_depth + 1);
	return AllFra * tMat->m_colour * GoTrace(FraRay, n_depth + 1);


}
void P3DRenderScene::RegisterMat(P3DMaterial* tMat){
	std::map<P3DMaterial*, int>::iterator it = m_MatToIndexMap.find(tMat);
	if (it == m_MatToIndexMap.end()){
		m_MatToIndexMap[tMat] = m_MatVec.size();
		m_MatVec.push_back(tMat);
	}
}

int P3DRenderScene::GetMatIndex(P3DMaterial* tMat){
	std::map<P3DMaterial*, int>::iterator it = m_MatToIndexMap.find(tMat);
	if (it == m_MatToIndexMap.end())
		RegisterMat(tMat);
	return m_MatToIndexMap[tMat];
}
