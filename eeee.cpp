#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include<time.h>

void randomreturn(int *x1, int *y1);
int pow1(int x, int y);

int desresult[256][640 * 800]; //[0~255]

int main()
{

	
	//이미지 로드
	cv::Mat image = cv::imread("img1.bmp");

	cv::Mat gray;

	cv::Mat eeee = cv::Mat::zeros(640, 800, CV_8UC1); //표기해줄곳

	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY); //그레이 스케일로

	cv::Mat widegray =  cv::Mat::zeros(666,826, CV_8UC1);

	cv::Mat imageROI(widegray, cv::Rect(13, 13, gray.cols, gray.rows));

	cv::Mat fimage = cv::Mat::zeros(666, 826, CV_8UC1);

	gray.copyTo(imageROI);

	const int width = image.cols;
	const int height = image.rows;
	// widegray에 큰 이미지로 복사가 되었음. 13만큼 더 늘어났음(경계값 처리를 위해)
	
	
	widegray.copyTo(fimage);

	

	
	
	cv::Mat des = cv::Mat::zeros(27,27,CV_8UC1); //디스크립터




	//라인 패턴을 생성하는 부분(중앙에 가깝게 랜덤으로)
	
	srand(time(NULL));
	int num = rand() % 100;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int x1x2equal = 0;// 0이면 같지 않은거 1이면 같은거(구분)
	int count = 0; // 1이면 1찾기, 2이면 2찾기
	int county = 0; // 1이면 1찾기, 2이면 2찾기
	//x1,x2찾기
	cv::Point savepoint[512];
	for (int i = 0; i < 256; i++) 
	{
		//첫번째 점
		randomreturn(&x1, &y1);
		//printf("x1 : %d, y1 : %d  \n\n", x1, y1);

		///////////////////////
		while (x1 == 13 && y1 == 13) //중앙일때는 randomreturn 중앙이 아닐때까지 반복
		{
			printf("첫번째점이 가운데점 검출되었으므로 다시 검사합니다. \n");
			randomreturn(&x1, &y1);
			printf("x1 : %d, y1 : %d  \n\n", x1, y1);
		}
		////////////////////////
		printf("-----------------------------\n");
		
		
		//두번째 점
		randomreturn(&x2, &y2);
		printf("x2 : %d, y2 : %d  \n\n", x2, y2);
		////////////////////////
		while (x2 == 13 && y2 == 13) //중앙일때는 randomreturn 중앙이 아닐때까지 반복
		{
			printf("두번째점이 가운데점 검출되었으므로 다시 검사합니다. \n");
			randomreturn(&x2, &y2);
			printf("x2 : %d, y2 : %d  \n\n", x1, y1);
		}
		///////////////////////

		while (x1 == x2 && y1 == y2)
		{
			printf("두 점이 같은점으로 검출되었으므로 두번째 점을 재배치합니다. \n");
			randomreturn(&x2, &y2);
			printf("x2 : %d, y2 : %d  \n\n", x1, y1);
		}

		printf("-----------------------------\n");

		
		cv::Point start_point(x1, y1);		//line의 시작점 
	cv::Point end_point(x2, y2);	//line의 끝점	

	// 파랑색 선으로 그리기. BGR순서
	cv::line(des, start_point, end_point, cv::Scalar(255,0, 0), 1);
	//이제 위 함수안에다가 최종 2차vector(x,y) 배열저장 해야함 홀수는 x1 짝수는 x2
	
	start_point = cv::Point(x1 - 13, y1 - 13);
	end_point = cv::Point(x2 - 13, y2 - 13);

	savepoint[2 * i] = start_point;
	savepoint[2 * i + 1] = end_point;
	}// 0,1 짝 2,3 짝 3,4 짝 이렇게 이루어짐
	
	
	
	

	//경계선 처리는 먼저 이미지를 좌 우 상 하 27씩 늘려서 0으로 초기화해주고 적용시키고
	//그다음 원래부분 옮겨서 이미지 표시
	//


	//int result[256][520000]; //[0~255][0~511999]

	int result[256]; //[0~255]
	


	int finalresult = 0;
	//라인 패턴을 해당 이미지에 적용해서 값들을 추출
	//image.rows
		//image.cols
	//printf("%d \n", pow1(10, 1));
	
	
	
	for (int r = 0; r < image.rows; r++) //그래도 계산할때는 r+13을 해줘야함 13,13에서부터 시작하기 때문
	{
		for (int c = 0; c < image.cols; c++) //마찬가지로 계산할때 c+13
		{

			for (int i = 0; i < 256; i++)
			{
				//printf("%d와 %d의 비교\n", widegray.at<uchar>(cv::Point(-13,-13) + savepoint[2 * i]), widegray.at<uchar>(cv::Point(-13, -13) + savepoint[2 * i + 1])); //해당 wide
				if (widegray.at<uchar>(cv::Point(c + 13, r + 13) + savepoint[2 * i]) > widegray.at<uchar>(cv::Point(c+ 13, r+13) + savepoint[2 * i + 1]))
				{
					result[i] = 1;
					//cv::circle(widegray, cv::Point(13 + c, 13 + r) + savepoint[2 * i],0.1, cv::Scalar(255, 0, 0), 1);
					desresult[i][r * c] = 1; //영구적으로 저장하기 위해서 descriptor만듬
				
				}
				else
				{
					result[i] = 0;
					//cv::circle(widegray, cv::Point(13 + c, 13 + r) + savepoint[2 * i + 1], 0.1, cv::Scalar(55,55, 55), 1);
					desresult[i][r * c] = 0; //영구적으로 저장하기 위해서 descriptor만듬
				}



			}
		//result처리가 끝나고 난다음 256개의 디스크립터에서 영상에 표시해주기 위해 8비트만 추출
			for (int i = 0; i < 8; i++)
			{
				finalresult = finalresult + (result[i] * pow1(2,i));
			}
			
			//printf("%d \n", finalresult);
			eeee.at<uchar>(cv::Point(c, r)) = finalresult - 125;
			finalresult = 0;
			//printf("명암값 : %d \n", finalresult);

		}

	}
	
	




	//디스크립터중 상위 8개만 추출하기






	//상위 값들 이미지로 표현









	//이미지에 line 그리는 방법
	//cv::Point start_point(width / 2, 0);		//line의 시작점 
	//cv::Point end_point(width / 2, height - 1);	//line의 끝점	

	// 파랑색 선으로 그리기. BGR순서
	//cv::line(image, start_point, end_point, cv::Scalar(255, 0, 0), 1); 

	cv::namedWindow("Result");
	
	//cv::imshow("Result", des);
	//cv::imwrite("Result.jpg", des);
	//des 출력
	cv::imshow("Result", eeee);
	cv::imshow("widegray", widegray);
	cv::imshow("descriptor", des);
	cv::imwrite("Result.jpg", eeee);

	
	cv::waitKey(0);

	return 0;
}


//x1과 y1의 값을 랜덤으로 중복되게 해서 준다.
void randomreturn(int *x1, int *y1)
{
	int count = 0; // 1이면 1찾기, 2이면 2찾기
	int num = 0;

	for (int i = 0; i < 2; i++) //x1,x2,y1,y2 네번 찾아야하기 때문에 포문 4번
	{ //13 13은 처음 시작점
		count++;
		num = rand() % 100;
		printf("x : %d \n", num);
		//1%의 확률
		
		if (num == 0)
		{

			printf("000 \n");
			if (count == 1)
			{
				*x1 = 0;
				printf("000 \n");
			}
			else if (count == 2)
			{
				*y1 = 0;
				printf("000 \n");

			}

		}

		else if (num == 1)
		{
			if (count == 1)
			{
				*x1 = 1;
			}
			else if (count == 2)
			{
				*y1 = 1;

			}

		}
		else if (num == 2)
		{
			if (count == 1)
			{
				*x1 = 2;
			}
			else if (count == 2)
			{
				*y1 = 2;

			}

		}

		else if (num == 3)
		{
			if (count == 1)
			{
				*x1 = 3;
			}
			else if (count == 2)
			{
				*y1 = 3;

			}
		}
		//2%의 확률
		else if (num >= 4 && num <= 5)
		{
			if (count == 1)
			{
				*x1 = 4;
			}
			else if (count == 2)
			{
				*y1 = 4;

			}
		}
		else if (num >= 6 && num <= 7)
		{
			if (count == 1)
			{
				*x1 = 5;
			}
			else if (count == 2)
			{
				*y1 = 5;
			}
		}
		else if (num >= 8 && num <= 9)
		{
			if (count == 1)
			{
				*x1 = 6;
			}
			else if (count == 2)
			{
				*y1 = 6;
			}
		}
		else if (num >= 10 && num <= 11)
		{
			if (count == 1)
			{
				*x1 = 7;
			}
			else if (count == 2)
			{
				*y1 = 7;
			}
		}
		//5%의 확률
		else if (num >= 12 && num <= 16)
		{
			if (count == 1)
			{
				*x1 = 8;
			}
			else if (count == 2)
			{
				*y1 = 8;
			}
		}
		else if (num >= 17 && num <= 21)
		{
			if (count == 1)
			{
				*x1 = 9;
			}
			else if (count == 2)
			{
				*y1 = 9;
			}
		}
		//7%의 확률
		else if (num >= 22 && num <= 28)
		{
			if (count == 1)
			{
				*x1 = 10;
			}
			else if (count == 2)
			{
				*y1 = 10;
			}
		}
		//8%의 확률
		else if (num >= 29 && num <= 36)
		{
			if (count == 1)
			{
				*x1 = 11;
			}
			else if (count == 2)
			{
				*y1 = 11;
			}
		}
		else if (num >= 37 && num <= 44)
		{
			if (count == 1)
			{
				*x1 = 12;
			}
			else if (count == 2)
			{
				*y1 = 12;
			}
		}

		//10%의 확률(가운데 예외처리 필요X 아직 x축이기 때문에)
		else if (num >= 45 && num <= 54)
		{
			if (count == 1)
			{
				*x1 = 13;
			}
			else if (count == 2)
			{
				*y1 = 13;
			}
		}

		//8%의 확률
		else if (num >= 55 && num <= 62)
		{
			if (count == 1)
			{
				*x1 = 14;
			}
			else if (count == 2)
			{
				*y1 = 14;
			}
		}
		else if (num >= 63 && num <= 70)
		{
			if (count == 1)
			{
				*x1 = 15;
			}
			else if (count == 2)
			{
				*y1 = 15;
			}
		}
		//7%의 확률
		else if (num >= 71 && num <= 77)
		{
			if (count == 1)
			{
				*x1 = 16;
			}
			else if (count == 2)
			{
				*y1 = 16;
			}
		}
		//5%의 확률
		else if (num >= 78 && num <= 82)
		{
			if (count == 1)
			{
				*x1 = 17;
			}
			else if (count == 2)
			{
				*y1 = 17;
			}
		}
		else if (num >= 83 && num <= 87)
		{
			if (count == 1)
			{
				*x1 = 18;
			}
			else if (count == 2)
			{
				*y1 = 18;
			}
		}
		//2%의 확률
		else if (num >= 88 && num <= 89)
		{
			if (count == 1)
			{
				*x1 = 19;
			}
			else if (count == 2)
			{
				*y1 = 19;
			}
		}
		else if (num >= 90 && num <= 91)
		{
			if (count == 1)
			{
				*x1 = 20;
			}
			else if (count == 2)
			{
				*y1 = 20;
			}
		}
		else if (num >= 92 && num <= 93)
		{
			if (count == 1)
			{
				*x1 = 21;
			}
			else if (count == 2)
			{
				*y1 = 21;
			}
		}
		else if (num >= 94 && num <= 95)
		{
			if (count == 1)
			{
				*x1 = 22;
			}
			else if (count == 2)
			{
				*y1 = 22;
			}
		}
		//1%의 확률
		else if (num == 96)
		{
			if (count == 1)
			{
				*x1 = 23;
			}
			else if (count == 2)
			{
				*y1 = 23;
			}
		}
		else if (num == 97)
		{
			if (count == 1)
			{
				*x1 = 24;
			}
			else if (count == 2)
			{
				*y1 = 24;
			}
		}
		else if (num == 98)
		{
			if (count == 1)
			{
				*x1 = 25;
			}
			else if (count == 2)
			{
				*y1 = 25;
			}
		}
		else if (num == 99)
		{
			if (count == 1)
			{
				*x1 = 26;
			}
			else if (count == 2)
			{
				*y1 = 26;
			}
		}



	}


	//*x1 = 4;
	//*y1 = 3;
}
//인트의 승을 구해준다.
int pow1(int x, int y)
{
	int i;
	int ret_val;
	if (y == 0)
	{
		return 1;
	}
	ret_val = x;

	for (i = 0; i < y - 1; i++)
	{
		ret_val = ret_val * x;
	}
	return ret_val;
}
