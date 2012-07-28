/** 
\file Camera.h
\brief ī�޶��� �Է� ���� ��� ����
*/

#pragma once
#include "../wonjo.h"
#include <opencv2/opencv.hpp>
#include "../dll_header.h"
#include "../global.h"
#include "../Results.h"
#define	defaultFileName	"/camera.txt"


<<<<<<< .mine
// #define FEATURE_WIDTH 30
// #define FEATURE_HEIGHT 50
#define FEATURE_WIDTH 89
#define FEATURE_HEIGHT 110
=======
#define FEATURE_WIDTH 46
#define FEATURE_HEIGHT 62
>>>>>>> .r87
/**
* \class CCamera 
* \brief ī�޶� ���� Ŭ����
* \remark  ī�޶��� �ùٸ� �Է��� ���� ����
* \param size ī�޶� ũ��
* \param projectionMatrix ī�޶��� projectionMatrix
* \param distortionFactor ī�޶��� distortionFactor
* \param parameterFile �Ķ���Ͱ� ����� ������ �̸��� ����� ����
* \param img_input ī�޶� ���� �ڵ鸵 ����
*/
class CCamera
{
public:
	CCamera(void); /**<������*/
	CCamera(bool	turnOn); /**<������*/


	Results featuresResult;

	~CCamera(void); /**<�Ҹ���*/

	// Intrinsic Parameters
	CvSize	size;
	double	projectionMatrix[3][4];
	double	distortionFactor[4];

	char	parameterFile[100];


	 // Intrinsic Parameters
    bool  _fIntrinsic;
	float camera_intrinsic[3][3];
	float camera_distortion[4];
	float camera_rotation[3];
	float camera_translation[3];
	CvMat intrinsic;
	CvMat distortion;
    CvMat rotation;
    CvMat translation;
    float camera_rotation3by3[3][3];
    CvMat rotation3by3;

    float projection_matrix[3][4];
    CvMat P;


	 //
    // Pose Estimation by Features
    //
    bool    _fPoseEstimatedByFeatures;
    bool    _fValidPose;
	float   _FeaturesRotation[3];
    float   _FeaturesRotation3by3[3][3];
	float   _FeaturesTranslation[3];
    float   _FeaturesQuaternion[4];

	
	CvMat   _FeaturesRotationMat;
    CvMat   _FeaturesRotation3by3Mat;
	CvMat   _FeaturesTranslationMat;
    CvMat   _FeaturesQuaternionMat;

	
	//
    // Camera Transform
    //
    float   _CameraCenterT[3];
    float   _CameraCenterR[3][3];
	float   _CameraCenterRTransPose[3][3];
	float   _CameraHomography[3][3];



    CvMat   _CameraCenterTMat;
    CvMat   _CameraCenterRMat;
	CvMat	_CameraCenterRTransPoseMat;
	CvMat	_CameraHomographyMat;

	 //
    // OpenGL View Frustrum
    //
    GLuint  _nCameraTexID;

    //
    // OpenGL ModelView Matrix
    //
    float   _ModelView[16];
	


	bool	loaded;


	CvMat QueryRotationMat();
    CvMat QueryTranslationMat();
    float * QueryModelViewMat();
    float QueryR( int i, int j ) { return _FeaturesRotation3by3[i][j]; }
    float QueryT( int i ) { return _FeaturesTranslation[i]; }
    float QueryCR( int i, int j ) { return _CameraCenterR[i][j]; }
    float QueryCT( int i ) { return _CameraCenterT[i]; }

    
    void RenderCaptureImage();

    float QueryFx();
    float QueryFy();


	void featurePoseEstimation();

	//3D ���� �׸��� ���ؼ� ������ �� �ΰ��� �Լ��� ȣ���Ѵ�.
	D3DXMATRIXA16* D3DXMakeProjectionMatrix(D3DXMATRIXA16* pOut);
	D3DXMATRIXA16* D3DXMakeViewMatrix(D3DXMATRIXA16* pOut);
	

	
	// Loading Functions
	/** 
	* \fn bool load	(const char* fileName)
	* \brief ī�޶� �Ķ���͸� �����ϴ� �Լ�.
	* \remark ���ǵ� fileName�� ��Camera.dat���� ������ �����Ͽ� Distortion Factor, ȭ�� ũ�⸦ �о� ī�޶� ����� �����ϰ� Projection Matrix�� �д´�.\n
	* ī�޶� ������ ������ ����ڰ� �ٲ� �� �ִµ� �̴� Camera.dat������ ���θ� ������ �־�� �Ѵ�. \n
	* �� ������ calibration �����Ϳ��� mapping�� ���Ͽ� camera parameter ���Ͽ��� �����ϵ��� ����Ǿ� �ִ�. \n
	* ���� ī�޶��� ����� �����ϰ��� �� ������ #size �κп� xũ�� (����) yũ�� �� �������� �Է��ϸ� �ȴ�.
	* \param fileName ������ ���ϸ�
	*/
	bool load	(const char* fileName);

	/** 
	* \fn bool load()
	* \brief ī�޶� �Ķ���͸� �����ϴ� �Լ�.
	* \remark ���ǵ� fileName�� ��Camera.dat���� ������ �����Ͽ� Distortion Factor, ȭ�� ũ�⸦ �о� ī�޶� ����� �����ϰ� Projection Matrix�� �д´�.\n
	* ī�޶� ������ ������ ����ڰ� �ٲ� �� �ִµ� �̴� Camera.dat������ ���θ� ������ �־�� �Ѵ�. \n
	* �� ������ calibration �����Ϳ��� mapping�� ���Ͽ� camera parameter ���Ͽ��� �����ϵ��� ����Ǿ� �ִ�. \n
	* ���� ī�޶��� ����� �����ϰ��� �� ������ #size �κп� xũ�� (����) yũ�� �� �������� �Է��ϸ� �ȴ�.
	*/
	bool	load()	{	return load(defaultFileName);		}

	// ���� 

	/** 
	* \fn void observ2Ideal(CvPoint	observed, CvPoint2D *ideal)
	* \brief ī�޶�� �Է� ���� ������ ��ǥ�� Ideal�� ��ǥ�� ��ȯ�ϴ� �Լ�.
	* \param observed ī�޶�� �Է� ���� ������ ��ǥ
	* \param ideal ideal�ϰ� ��ȯ�� ������ ��ǥ
	*/
	void observ2Ideal(CvPoint	observed, CvPoint2D *ideal);

	/** 
	* \fn void ideal2Observ(CvPoint2D ideal, CvPoint *observed)
	* \brief ī�޶�� �Է� ���� ������ ��ǥ�� observed�� ��ǥ�� ��ȯ�ϴ� �Լ�.
	* \param ideal �Է¹��� ������ ��ǥ
	* \param observed observed�ϰ� ��ȯ�� ������ ��ǥ
	*/
	void ideal2Observ(CvPoint2D ideal, CvPoint *observed);


	/** 
	* \fn void ideal2Observ(CvPoint2D ideal, CvPoint2D *observed)
	* \brief ī�޶�� �Է� ���� ������ ��ǥ�� observed�� ��ǥ�� ��ȯ�ϴ� �Լ�.
	* \param ideal �Է¹��� ������ ��ǥ
	* \param observed observed�ϰ� ��ȯ�� ������ ��ǥ
	*/
	void ideal2Observ(CvPoint2D ideal, CvPoint2D *observed);

	/** 
	* \fn void observ2Ideal(int ox, int oy, ARTKFloat *ix, ARTKFloat *iy)
	* \brief ī�޶�� �Է� ���� ������ ��ǥ�� Ideal�� ��ǥ�� ��ȯ�ϴ� �Լ�.
	* \param ox ī�޶�� �Է� ���� ������ x��ǥ
	* \param oy ī�޶�� �Է� ���� ������ y��ǥ
	* \param ix ideal�ϰ� ��ȯ�� ������ x��ǥ
	* \param iy ideal�ϰ� ��ȯ�� ������ y��ǥ
	*/
	void observ2Ideal(int ox, int oy, ARTKFloat *ix, ARTKFloat *iy);

	

	CvMat*					m_ExtrinsicParam; //ī�޶��� �ܺ� �Ķ���ͷ� �� ���� ���� 3���� ��ǥ������ �̷������.
	CvMat*					m_MatHomography; //ȣ��׷���
	
	//ȣ��׷��Ǹ� �����ϱ� ���� ����
	CvMat*					m_vecRotX;
	CvMat*					m_vecRotY;
	CvMat*					m_vecRotZ;
	CvMat*					m_vecTrans;
	CvMat*					m_Rotation3x3;
	CvMat*					m_Rotation3x1;
	CvMat*					m_RotationTranspose3x3;



	CvMat*					m_IntrinsicParam; //ī�޶��� ���� �Ķ���ͷ� ������ ���� ����Ѵ�.
	CvMat*					m_IntrinsicParamInv; //ī�޶� ���� �Ķ������ �����

	CvMat* calcHomography(CvMat* src, CvMat* dst);
	void ZhangCalibration(CvMat* m_RealCornerPosition, CvMat* imgCornerPosition);



};	// end of class

//};};		// end of namespace