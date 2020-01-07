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

	
	//�̹��� �ε�
	cv::Mat image = cv::imread("img1.bmp");

	cv::Mat gray;

	cv::Mat eeee = cv::Mat::zeros(640, 800, CV_8UC1); //ǥ�����ٰ�

	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY); //�׷��� �����Ϸ�

	cv::Mat widegray =  cv::Mat::zeros(666,826, CV_8UC1);

	cv::Mat imageROI(widegray, cv::Rect(13, 13, gray.cols, gray.rows));

	cv::Mat fimage = cv::Mat::zeros(666, 826, CV_8UC1);

	gray.copyTo(imageROI);

	const int width = image.cols;
	const int height = image.rows;
	// widegray�� ū �̹����� ���簡 �Ǿ���. 13��ŭ �� �þ��(��谪 ó���� ����)
	
	
	widegray.copyTo(fimage);

	

	
	
	cv::Mat des = cv::Mat::zeros(27,27,CV_8UC1); //��ũ����




	//���� ������ �����ϴ� �κ�(�߾ӿ� ������ ��������)
	
	srand(time(NULL));
	int num = rand() % 100;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int x1x2equal = 0;// 0�̸� ���� ������ 1�̸� ������(����)
	int count = 0; // 1�̸� 1ã��, 2�̸� 2ã��
	int county = 0; // 1�̸� 1ã��, 2�̸� 2ã��
	//x1,x2ã��
	cv::Point savepoint[512];
	for (int i = 0; i < 256; i++) 
	{
		//ù��° ��
		randomreturn(&x1, &y1);
		//printf("x1 : %d, y1 : %d  \n\n", x1, y1);

		///////////////////////
		while (x1 == 13 && y1 == 13) //�߾��϶��� randomreturn �߾��� �ƴҶ����� �ݺ�
		{
			printf("ù��°���� ����� ����Ǿ����Ƿ� �ٽ� �˻��մϴ�. \n");
			randomreturn(&x1, &y1);
			printf("x1 : %d, y1 : %d  \n\n", x1, y1);
		}
		////////////////////////
		printf("-----------------------------\n");
		
		
		//�ι�° ��
		randomreturn(&x2, &y2);
		printf("x2 : %d, y2 : %d  \n\n", x2, y2);
		////////////////////////
		while (x2 == 13 && y2 == 13) //�߾��϶��� randomreturn �߾��� �ƴҶ����� �ݺ�
		{
			printf("�ι�°���� ����� ����Ǿ����Ƿ� �ٽ� �˻��մϴ�. \n");
			randomreturn(&x2, &y2);
			printf("x2 : %d, y2 : %d  \n\n", x1, y1);
		}
		///////////////////////

		while (x1 == x2 && y1 == y2)
		{
			printf("�� ���� ���������� ����Ǿ����Ƿ� �ι�° ���� ���ġ�մϴ�. \n");
			randomreturn(&x2, &y2);
			printf("x2 : %d, y2 : %d  \n\n", x1, y1);
		}

		printf("-----------------------------\n");

		
		cv::Point start_point(x1, y1);		//line�� ������ 
	cv::Point end_point(x2, y2);	//line�� ����	

	// �Ķ��� ������ �׸���. BGR����
	cv::line(des, start_point, end_point, cv::Scalar(255,0, 0), 1);
	//���� �� �Լ��ȿ��ٰ� ���� 2��vector(x,y) �迭���� �ؾ��� Ȧ���� x1 ¦���� x2
	
	start_point = cv::Point(x1 - 13, y1 - 13);
	end_point = cv::Point(x2 - 13, y2 - 13);

	savepoint[2 * i] = start_point;
	savepoint[2 * i + 1] = end_point;
	}// 0,1 ¦ 2,3 ¦ 3,4 ¦ �̷��� �̷����
	
	
	
	

	//��輱 ó���� ���� �̹����� �� �� �� �� 27�� �÷��� 0���� �ʱ�ȭ���ְ� �����Ű��
	//�״��� �����κ� �Űܼ� �̹��� ǥ��
	//


	//int result[256][520000]; //[0~255][0~511999]

	int result[256]; //[0~255]
	


	int finalresult = 0;
	//���� ������ �ش� �̹����� �����ؼ� ������ ����
	//image.rows
		//image.cols
	//printf("%d \n", pow1(10, 1));
	
	
	
	for (int r = 0; r < image.rows; r++) //�׷��� ����Ҷ��� r+13�� ������� 13,13�������� �����ϱ� ����
	{
		for (int c = 0; c < image.cols; c++) //���������� ����Ҷ� c+13
		{

			for (int i = 0; i < 256; i++)
			{
				//printf("%d�� %d�� ��\n", widegray.at<uchar>(cv::Point(-13,-13) + savepoint[2 * i]), widegray.at<uchar>(cv::Point(-13, -13) + savepoint[2 * i + 1])); //�ش� wide
				if (widegray.at<uchar>(cv::Point(c + 13, r + 13) + savepoint[2 * i]) > widegray.at<uchar>(cv::Point(c+ 13, r+13) + savepoint[2 * i + 1]))
				{
					result[i] = 1;
					//cv::circle(widegray, cv::Point(13 + c, 13 + r) + savepoint[2 * i],0.1, cv::Scalar(255, 0, 0), 1);
					desresult[i][r * c] = 1; //���������� �����ϱ� ���ؼ� descriptor����
				
				}
				else
				{
					result[i] = 0;
					//cv::circle(widegray, cv::Point(13 + c, 13 + r) + savepoint[2 * i + 1], 0.1, cv::Scalar(55,55, 55), 1);
					desresult[i][r * c] = 0; //���������� �����ϱ� ���ؼ� descriptor����
				}



			}
		//resultó���� ������ ������ 256���� ��ũ���Ϳ��� ���� ǥ�����ֱ� ���� 8��Ʈ�� ����
			for (int i = 0; i < 8; i++)
			{
				finalresult = finalresult + (result[i] * pow1(2,i));
			}
			
			//printf("%d \n", finalresult);
			eeee.at<uchar>(cv::Point(c, r)) = finalresult - 125;
			finalresult = 0;
			//printf("��ϰ� : %d \n", finalresult);

		}

	}
	
	




	//��ũ������ ���� 8���� �����ϱ�






	//���� ���� �̹����� ǥ��









	//�̹����� line �׸��� ���
	//cv::Point start_point(width / 2, 0);		//line�� ������ 
	//cv::Point end_point(width / 2, height - 1);	//line�� ����	

	// �Ķ��� ������ �׸���. BGR����
	//cv::line(image, start_point, end_point, cv::Scalar(255, 0, 0), 1); 

	cv::namedWindow("Result");
	
	//cv::imshow("Result", des);
	//cv::imwrite("Result.jpg", des);
	//des ���
	cv::imshow("Result", eeee);
	cv::imshow("widegray", widegray);
	cv::imshow("descriptor", des);
	cv::imwrite("Result.jpg", eeee);

	
	cv::waitKey(0);

	return 0;
}


//x1�� y1�� ���� �������� �ߺ��ǰ� �ؼ� �ش�.
void randomreturn(int *x1, int *y1)
{
	int count = 0; // 1�̸� 1ã��, 2�̸� 2ã��
	int num = 0;

	for (int i = 0; i < 2; i++) //x1,x2,y1,y2 �׹� ã�ƾ��ϱ� ������ ���� 4��
	{ //13 13�� ó�� ������
		count++;
		num = rand() % 100;
		printf("x : %d \n", num);
		//1%�� Ȯ��
		
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
		//2%�� Ȯ��
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
		//5%�� Ȯ��
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
		//7%�� Ȯ��
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
		//8%�� Ȯ��
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

		//10%�� Ȯ��(��� ����ó�� �ʿ�X ���� x���̱� ������)
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

		//8%�� Ȯ��
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
		//7%�� Ȯ��
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
		//5%�� Ȯ��
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
		//2%�� Ȯ��
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
		//1%�� Ȯ��
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
//��Ʈ�� ���� �����ش�.
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
