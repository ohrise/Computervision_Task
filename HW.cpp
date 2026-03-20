//cropping의 경우 esc를 눌러야 brek가 됩니다
//contrast는 변수를 스피너를 이용하여 변경시킨 후 다른 키를 눌렀다가 다시 해당 항목으로 들어가야 실시됩니다.
#include <GL/glui.h>
#include <opencv2/opencv.hpp>
#include<iostream>
#include "OpenFileDialog.h"
#include "SaveFileDialog.h"

using namespace std;
using namespace cv;

int PEN, LINE, CIRCLE, RECANGLE = 0;
int draw_pen, draw_line, draw_Rectangel, draw_Circle = 0;
int LINEAR_CONTRAST, INVERSE, GAMMA_CORRECTION, THRESHOLDING = 0;
int radio2, radio3, radio4 = 0;
int thick = 1;
int R, G, B, T, V = 0;
int x1, yy1, x2, yy2;// 마우스 지정 좌표
int drawing = 0;
int v1 = 30;
int b1 = 20;
int v2 = 220;
int b2 = 220;
int TH = 0;
float gamma_v = 0.5;
int cx1, cy1, cx2, cy2;// 마우스로 지정한 사각형의 좌표

Mat imgclone, imgcloned, img, roi, result;
GLUI_Button* croppingButton;
String Filename;
GLUI_Panel* p5;
GLUI_Panel* p9;
GLUI_Spinner* sp1;
GLUI_Spinner* sp2;
GLUI_Spinner* sp3;
GLUI_Spinner* sp4;
GLUI_Spinner* sp5;
GLUI_Spinner* sp6;
GLUI_Spinner* sp7;
GLUI_Spinner* sp8;
GLUI_Spinner* sp9;
GLUI_Spinner* sp10;
GLUI_Spinner* sp11;
GLUI_Rollout* r1;
GLUI_Rollout* r2;
GLUI_Rollout* r3;
GLUI_RadioGroup* rg4;
GLUI_RadioGroup* rg2;
GLUI_Checkbox* che;



//문서 열기
void open_callback(int id)
{
	OpenFileDialog* openFileDialog = new OpenFileDialog();
	if (openFileDialog->ShowDialog()) {
		Filename = openFileDialog->FileName;
		cout << "선택한 파일: " << Filename << endl;
		img = imread(Filename);
		p5->enable();
		if (img.empty()) {
			cout << "이미지 로딩 오류." << endl;
			exit(0);
		}
		imshow("img", img);
		imgclone = img.clone();
		imshow("img.원본", imgclone);
	}

}

void onMouse(int event, int x, int y, int flags, void* param) {
	if (event == EVENT_LBUTTONDOWN) {
		drawing = 1;
		cx1 = x;
		cy1 = y;
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (drawing == 1) {
			cx2 = x;
			cy2 = y;
			img = imgclone.clone();
			rectangle(img, Rect(cx1, cy1, cx2 - cx1, cy2 - cy1), Scalar(0, 255, 0), 2);
			imshow("img", img);
		}
	}
	else if (event == EVENT_LBUTTONUP) {
		drawing = 0;

		roi = img(Rect(cx1, cy1, cx2 - cx1, cy2 - cy1));

		if (!roi.empty()) {
			img = roi.clone();  // 크롭된 영역을 원본 이미지로 설정
			imshow("img", img);
		}
		else {
			// 예외 처리 또는 오류 메시지 표시
			cerr << "ROI is empty!" << endl;
		}
	}
}

void cropping_callback(int id) {
	imgcloned = img.clone();
	setMouseCallback("img", onMouse);

	while (true) {
		int key = waitKey(30);  // 30 밀리초 동안 대기

		if (key == 27) {  // ESC 키를 누르면 종료
			break;
		}
	}
}



void quitCallback(int id) {
	exit(0);
}
void testscroll_T(int id)
{
	thick = 1 + sp1->get_int_val();
	GLUI_Master.sync_live_all();
	glutPostRedisplay();
}
void testscroll_R(int id)
{
	R = sp2->get_int_val();
	GLUI_Master.sync_live_all();
	glutPostRedisplay();
}
void testscroll_G(int id)
{
	G = sp3->get_int_val();
	GLUI_Master.sync_live_all();
	glutPostRedisplay();
}
void testscroll_B(int id)
{
	B = sp4->get_int_val();
	GLUI_Master.sync_live_all();
	glutPostRedisplay();
}
void testscroll_V(int id)
{
	V = sp5->get_int_val();
	GLUI_Master.sync_live_all();
	glutPostRedisplay();
}
void save_callback(int id)
{
	SaveFileDialog* saveFileDialog = new SaveFileDialog();
	if (saveFileDialog->ShowDialog()) {
		Filename = saveFileDialog->FileName;

		std::string extension = ".png";
		if (Filename.find(extension) == std::string::npos) {
			Filename += extension;
		}
		imwrite(Filename, img);  // img 변수를 사용하여 이미지를 저장
	}
}
void testscroll_X1(int id)
{
	v1 = sp5->get_int_val();
}
void testscroll_Y1(int id)
{
	b1 = sp6->get_int_val();
}
void testscroll_X2(int id)
{
	v2 = sp7->get_int_val();
}
void testscroll_Y2(int id)
{
	b2 = sp8->get_int_val();
}
void testscroll_TH(int id)
{
	TH = sp11->get_int_val();
}
void testscroll_GA(int id)
{
	gamma_v = sp9->get_float_val();
}


// 펜 그리기
void drawPen(int event, int x, int y, int, void* param) {
	if (event == EVENT_LBUTTONDOWN) {
		drawing = true;
		circle(img, Point(x, y), 1, Scalar(B, G, R), T);
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (drawing == true)
			circle(img, Point(x, y), 1, Scalar(B, G, R), T);

	}
	else if (event == EVENT_LBUTTONUP)
		drawing = false;
	imshow("img", img);
}


// 선 그리기
void drawLine(int event, int x, int y, int, void* param) {
	if (event == EVENT_LBUTTONDOWN) {
		drawing = 1;
		x1 = x;
		yy1 = y;
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (drawing == 1) {
			x2 = x;
			yy2 = y;
		}
	}
	else if (event == EVENT_LBUTTONUP) {
		line(img, Point(x1, yy1), Point(x2, yy2), Scalar(B, G, R), T);

		imshow("img", img);
		drawing = 0;
	}
}

// 사각형 그리기

void drawRectangel(int event, int x, int y, int, void* param) {
	if (event == EVENT_LBUTTONDOWN) {// 마우스의 왼쪽 버튼을 누르면
		drawing = 1;
		x1 = x;    yy1 = y; // 사각형의 좌측 상단 좌표 저장
	}
	else if (event == EVENT_MOUSEMOVE) {
		if (drawing == 1) {
		}
	}
	else if (event == EVENT_LBUTTONUP) {// 마우스의 왼쪽 버튼에서 손을 떼면
		x2 = x;    yy2 = y;       // 사각형의 우측 하단 좌표 저장
		rectangle(img, Point(x1, yy1), Point(x2, yy2), Scalar(B, G, R), thick);
		imshow("img", img);
		drawing = 0;
	}

}

// 원 그리기
void drawCircle(int event, int x, int y, int, void* param) {
	if (event == EVENT_LBUTTONDOWN) {
		drawing = 1;
		x1 = x;
		yy1 = y;
	}
	else if (event == EVENT_MOUSEMOVE && drawing) {
		drawing = 1;
	}
	else if (event == EVENT_LBUTTONUP && drawing) {
		x2 = x;
		yy2 = y;
		if (che->get_int_val() == 1) {
			thick = -1;
		}
		circle(img, Point((x1 + x2) / 2, (yy1 + yy2) / 2), static_cast<int>(sqrt(pow(x2 - x1, 2) + pow(yy2 - yy1, 2)) / 2), Scalar(B, G, R), thick);
		imshow("img", img);
		drawing = 0;
	}
}
Mat gammaAdjust(const Mat& src)
{
	float gamma = sp9->get_float_val();  // 스피너에서 직접 값을 가져옴
	Mat img = src.clone();  // 복사본을 만들어 수정

	Mat table(1, 256, CV_8U);
	uchar* p = table.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

	LUT(img, table, img);  // 복사본을 사용하여 수정

	return img.clone();  // 수정된 이미지를 반환
}




//선형
int contrastEnh(int V, int x1, int y1, int x2, int y2) {
	float output = 0.0;  // output 변수를 초기화

	if (x1 == 0) {
		output = y1;  // x1이 0이면 그냥 y1 값을 사용
	}
	else if (0 <= V && V <= 1) {
		output = y1 / x1 * V;
	}
	else if (x1 < V && V <= x2) {
		output = ((y2 - y1) / (x2 - x1)) * (V - x1) + y1;
	}
	else if (x2 < V && V <= 255) {
		output = ((255 - y2) / (255 - x2)) * (V - x2) + y2;
	}

	return static_cast<int>(output);
}





Mat line_con(const Mat& input_img, int v1, int b1, int v2, int b2) {
	Mat img = input_img.clone();  // 복제된 이미지 생성

	if (img.channels() == 1) {
		for (int r = 0; r < img.rows; r++) {
			for (int c = 0; c < img.cols; c++) {
				int output = contrastEnh(img.at<uchar>(r, c), v1, b1, v2, b2);
				img.at<uchar>(r, c) = saturate_cast<uchar>(output);
				// 이후 output을 사용하여 이미지 처리
			}
		}
	}
	else if (img.channels() == 3) {
		for (int r = 0; r < img.rows; r++) {
			for (int c = 0; c < img.cols; c++) {
				for (int ch = 0; ch < img.channels(); ch++) {
					int output = contrastEnh(img.at<Vec3b>(r, c)[ch], v1, b1, v2, b2);
					img.at<Vec3b>(r, c)[ch] = saturate_cast<uchar>(output);
				}
			}
		}
	}
	return img;  // 결과 이미지 반환
}

//반전
void inverse() {
	if (img.channels() == 1) {
		img = 255 - img;
	}
	else if (img.channels() == 3) {
		img = Scalar(255, 255, 255) - img;
	}
	imshow("dst2", img);
}
//이진화

void checkbox1(int id)
{
	switch (radio2) {
	case -1: break;
	case 0:  break;
	case 1: che->disable();
		setMouseCallback("img", drawPen); break;
	case 2: che->disable();
		setMouseCallback("img", drawLine); break;
	case 3:che->enable();
		setMouseCallback("img", drawRectangel); break;
	case 4: che->enable();
		setMouseCallback("img", drawCircle); break;
	}
}
void checkbox2(int id)
{
	switch (radio3) {
	case -1:r1, r2, r3->disable(); break;
	case 0: r1, r2, r3->disable(); break;
	case 1:
		r1->enable();
		sp5->enable();
		sp6->enable();
		sp7->enable();
		sp8->enable();
		r2, r3->disable();
		img = line_con(img, v1, b1, v2, b2);
		break;
	case 2:
		p9->disable();
		inverse();
		break;
	case 3:
		r1->disable();
		r2->enable();
		sp9->enable();
		r3->disable();
		img = gammaAdjust(imgclone);
		break;
	case 4:
		r1, r2->disable();
		r3->enable();
		rg4->enable();
		sp11->enable();
		switch (radio4) {
		case -1: break;
		case 0:  break;
		case 1:TH = sp11->get_int_val();
			threshold(imgclone, img, TH, 255, THRESH_BINARY); break;
		case 2:TH = sp11->get_int_val();
			threshold(imgclone, img, TH, 255, THRESH_BINARY_INV); break;
		case 3:TH = sp11->get_int_val();
			threshold(imgclone, img, TH, 255, THRESH_TRUNC); break;
		case 4:TH = sp11->get_int_val();
			threshold(imgclone, img, TH, 255, THRESH_TOZERO_INV); break;
		case 5:TH = sp11->get_int_val();
			threshold(imgclone, img, TH, 255, THRESH_TOZERO); break;
		}
		break;
	}
	imshow("dst2", img);
	glutPostRedisplay();  // 화면 갱신을 요청
}

int main(int argc, char* argv[])

{
	glutInit(&argc, argv);
	GLUI_Master.set_glutIdleFunc(NULL);
	GLUI* glui = GLUI_Master.create_glui("Menu", 0, 0, 0);
	//////////////////////////////////////////////////컨트롤 자리//////////////////////////////////////////////////////////////////
	GLUI_Button* b1 = glui->add_button("READ", 0, open_callback);
	GLUI_Button* quiteButton = glui->add_button("Quite", 0, quitCallback);

	glui->add_separator();
	p5 = glui->add_panel("1", GLUI_PANEL_EMBOSSED);
	p5->disable();

	croppingButton = glui->add_button_to_panel(p5, "Cropping", 0, cropping_callback);
	GLUI_Button* saveButton = glui->add_button_to_panel(p5, "Save", 0, save_callback);


	GLUI_Panel* p6 = glui->add_panel_to_panel(p5, "2", GLUI_PANEL_EMBOSSED);
	p6->disable();
	rg2 = glui->add_radiogroup_to_panel(p6, &radio2, -1, checkbox1);
	glui->add_radiobutton_to_group(rg2, "");
	glui->add_radiobutton_to_group(rg2, "PEN");
	glui->add_radiobutton_to_group(rg2, "LINE");
	glui->add_radiobutton_to_group(rg2, "RECTANGLE");
	glui->add_radiobutton_to_group(rg2, "CIRCLE");


	glui->add_column_to_panel(p6, false);
	GLUI_Panel* p8 = glui->add_panel_to_panel(p6, "3", GLUI_PANEL_EMBOSSED);

	sp1 = glui->add_spinner_to_panel(p8, "THICK", GLUI_SPINNER_INT, &T, 1, testscroll_T);
	sp1->set_speed(0.01);
	sp1->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	glui->add_separator_to_panel(p8);
	sp2 = glui->add_spinner_to_panel(p8, "RED", GLUI_SPINNER_INT, &R, 1, testscroll_R);
	sp2->set_speed(0.01);
	sp2->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	glui->add_separator_to_panel(p8);
	sp3 = glui->add_spinner_to_panel(p8, "GREEN", GLUI_SPINNER_INT, &G, 1, testscroll_G);
	sp3->set_speed(0.01);
	sp3->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	glui->add_separator_to_panel(p8);
	sp4 = glui->add_spinner_to_panel(p8, "BLUE", GLUI_SPINNER_INT, &B, 1, testscroll_B);
	sp4->set_speed(0.01);
	sp4->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	che = glui->add_checkbox_to_panel(p8, "Fill", 0);

	GLUI_Panel* p7 = glui->add_panel_to_panel(p5, "6", GLUI_PANEL_EMBOSSED);
	GLUI_RadioGroup* rg3 = glui->add_radiogroup_to_panel(p7, &radio3, -1, checkbox2);
	glui->add_radiobutton_to_group(rg3, "");
	glui->add_radiobutton_to_group(rg3, "LINEAR CONTRAST");
	glui->add_radiobutton_to_group(rg3, "INVERSE");
	glui->add_radiobutton_to_group(rg3, "GAMMA CORRECTION");
	glui->add_radiobutton_to_group(rg3, "THRESHOLDING");

	glui->add_column_to_panel(p7, false);
	p9 = glui->add_panel_to_panel(p7, "7", GLUI_PANEL_EMBOSSED);

	r1 = glui->add_rollout_to_panel(p9, "LINEAR CONTRAST", false);
	r2 = glui->add_rollout_to_panel(p9, "GAMMA CORRECTION", false);
	r3 = glui->add_rollout_to_panel(p9, "THRESHOLDING", false);

	// LINERCONTRAST//
	sp5 = glui->add_spinner_to_panel(r1, "X1", GLUI_SPINNER_INT, &v1, 1, testscroll_X1);
	sp5->set_speed(0.01);
	sp5->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	glui->add_separator_to_panel(r1);
	sp6 = glui->add_spinner_to_panel(r1, "Y1", GLUI_SPINNER_INT, &b1, 1, testscroll_Y1);
	sp6->set_speed(0.01);
	sp6->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	glui->add_separator_to_panel(r1);
	sp7 = glui->add_spinner_to_panel(r1, "X2", GLUI_SPINNER_INT, &v2, 1, testscroll_X2);
	sp7->set_speed(0.01);
	sp7->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);

	glui->add_separator_to_panel(r1);
	sp8 = glui->add_spinner_to_panel(r1, "Y2", GLUI_SPINNER_INT, &b2, 1, testscroll_Y2);
	sp8->set_speed(0.01);
	sp8->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);
	//Gamma
	sp9 = glui->add_spinner_to_panel(r2, "GAMMAVALUE", GLUI_SPINNER_FLOAT, &gamma_v, 1, testscroll_GA);
	sp9->set_speed(0.1);  // 0.1 단위로 증가하도록 설정
	sp9->set_float_limits(0.001, 50.0, GLUI_LIMIT_CLAMP);  // 최소값과 최대값 설정


	//THRESHOLD
	rg4 = glui->add_radiogroup_to_panel(r3, &radio4, -1, checkbox2);
	glui->add_radiobutton_to_group(rg4, "");
	glui->add_radiobutton_to_group(rg4, "THRESH BINARY");
	glui->add_radiobutton_to_group(rg4, "THRESH BINARY INV");
	glui->add_radiobutton_to_group(rg4, "THRESH TRUNC");
	glui->add_radiobutton_to_group(rg4, "THRESH TOZERO INV");
	glui->add_radiobutton_to_group(rg4, "THRESH TOZERO");
	sp11 = glui->add_spinner_to_panel(r3, "THRESHOLDVALUE", GLUI_SPINNER_INT, &TH, 1, testscroll_TH);
	sp11->set_speed(0.01);
	sp11->set_int_limits(0, 255, GLUI_LIMIT_CLAMP);


	int main_window = glui->get_glut_window_id(); //glut윈도우의 번호 리턴를 정수 변수에 넣기
	glui->set_main_gfx_window(main_window); //window 알려줌
	glutMainLoop();  //계속 루프
}