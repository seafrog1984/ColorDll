// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� COLORDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// COLORDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef COLORDLL_EXPORTS
#define COLORDLL_API __declspec(dllexport)
#else
#define COLORDLL_API __declspec(dllimport)
#endif

#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>

using namespace cv;

//// �����Ǵ� ColorDll.dll ������
//class COLORDLL_API CColorDll {
//public:
//	CColorDll(void);
//	// TODO:  �ڴ�������ķ�����
//};
//
//extern COLORDLL_API int nColorDll;

COLORDLL_API int CalROI(Mat &img,int &sx, int &sy, int &w, int &h,int roi_border);//��ͼ��img�ϣ�(sx,sy)λ��ʼ�㣬w*h�ļ�������У���ȡ��ֽ���򣬲���������roi_border���أ����¼������
COLORDLL_API void CalRGB(Mat &img, int &sx, int &sy, int &w, int &h, int &r, int &g, int &b);//����img�ϣ�(sx,sy)λ��ʼ�㣬w*h�������У�r,g,b��ͨ����ƽ��ֵ
COLORDLL_API int CompareRGB(int &r, int &g, int &b,int dst_r,int dst_g,int dst_b, int thre);//�Ƚ�������ɫ�Ƿ���ͬ����ֵС��thre��Ϊ��ɫ��ͬ
