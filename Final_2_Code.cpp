#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define N 372 /* frame dimension for QCIF format */
#define M 496 /* frame dimension for QCIF format */
#define filename "cherry_496x372_444.yuv"
#define file_yuv "final_cherry_496x372_444_output.yuv"

/* code for armulator*/
#pragma arm section zidata="ram"
unsigned  char current_y[N][M];
unsigned  char current_u[N][M];
unsigned  char current_v[N][M];
#pragma arm section


int i,j;

int NH = 100;  //number of horizontal blocks
int NV = 100;  //number of vertical blocks

int rows = N;  //image hight
int columns = M;  //image width

float BWactual = 1.0*columns/NH;
int BW = columns/NH;

float BHactual = 1.0*rows/NV;
int BH = rows/NV;

int diffW = columns - (BW*NH);
int diffH = rows - (BH*NV);

	
bool invRandW =1;
bool invRandH =1;

int sizeW = diffW;
int sizeH = diffH;

int resize_num_BW = 0;
int resize_num_BH = 0;

//READ
void read()
{
  FILE *frame_c;
  if((frame_c=fopen(filename,"rb"))==NULL)
  {
    printf("current frame doesn't exist\n");
    exit(-1);
  }
  
  int NM = N*M;
  unsigned  char *py = &current_y[0][0];
  unsigned  char *pu = &current_u[0][0];
  unsigned  char *pv = &current_v[0][0];
  
  for(int i=0;i<NM;i=i+8){
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  	*py++ = fgetc(frame_c);
  }
  for(int i=0;i<NM;i=i+8){
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  	*pu++ = fgetc(frame_c);
  }
  for(int i=0;i<NM;i=i+8){
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  	*pv++ = fgetc(frame_c);
  } 
  
  fclose(frame_c);
 
}

// WRITE
void write()
{
  FILE *frame_yuv;
  frame_yuv=fopen(file_yuv,"wb");
  

  int NM = N * M;
  unsigned  char* py = &current_y[0][0];
  unsigned  char* pu = &current_u[0][0];
  unsigned  char* pv = &current_v[0][0];

  for (int i = 0; i < NM; i= i+8) {
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	  fputc(*py++, frame_yuv);
	
  }
  for (int i = 0; i < NM; i=i+8) {
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	  fputc(*pu++, frame_yuv);
	
  }
  for (int i = 0; i < NM; i=i+8) {
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);
	  fputc(*pv++, frame_yuv);

  }

	
  fclose(frame_yuv);

}


// RANDOM ARRAY
int* Create_Random_Array_W(int size,int lower_lim = 0,int upper_lim = 100){
	
	//srand((unsigned)time( NULL));
	static int *rand_array;
	rand_array = (int*)calloc(size, sizeof(int));
	
		int k=0;
		while(k<size){
		
		int random_number = (rand() %(upper_lim - lower_lim + 1)) + lower_lim;;		
    	bool isElementPresent = 0;
    	for (int i = 0; i <size; i++) {
        	if (rand_array[i] == random_number) {
            	isElementPresent = 1;
            	break;
        	}
    	}
    	if(isElementPresent == 0){
			rand_array[k] = random_number;
			int temp=0;
			
			for(int i=0;i<k;i++){
				
				if(rand_array[k-i] < rand_array[k-i-1]){   					
	            	temp = rand_array[k-i];
	            	rand_array[k-i] = rand_array[k-i-1];
	            	rand_array[k-i-1] = temp;
	           }
	        	else{
	        		break;
			   }
				
			}
			k++;
		}
	}
	
	return rand_array;   
	
}



// CREATE IMAGE
void Create_Image(int rand_arrayW[],int rand_arrayH[],int resize_num_BW,int resize_num_BH){
	
	BW = (resize_num_BW == -1) ? BW + 1 : BW;
	BH = (resize_num_BH == -1) ? BH + 1 : BH;

	int BWm = BW;
	int BHm = BH;
	int rw=0,rh=0;
	int hor_block=0,ver_block=0;
	
	for(int i=0;i<rows;i+=BHm){

		BHm = BH;

		if(ver_block == rand_arrayH[rh]){
			BHm += resize_num_BH;
			rh++;
		} 

		for(int j=0;j<columns;j+=BWm){

			BWm = BW;

			if(hor_block == rand_arrayW[rw]){
				BWm += resize_num_BW;
				rw++;
			}
			
			int sum_y=0,sum_u=0,sum_v=0;
			int mean_y=0,mean_u=0,mean_v=0;
			
			for(int k=0;k<BHm;k++){
				for (int o=0;o<BWm;o++){
					sum_y = sum_y + current_y[i+k][j+o];
					sum_u = sum_u + current_u[i+k][j+o];
					sum_v = sum_v + current_v[i+k][j+o];
				}
			}
			
			int BWmBHm = BWm*BHm;
			
			mean_y = sum_y/BWmBHm;
			mean_u = sum_u/BWmBHm;
			mean_v = sum_v/BWmBHm;
			
			for(int k=0;k<BHm;k++){
				for (int o=0;o<BWm;o++){
					current_y[i+k][j+o] = mean_y;
					current_u[i+k][j+o] = mean_u;
					current_v[i+k][j+o] = mean_v;
				}
			}

			hor_block++;
		}
		ver_block++;
	}
}



// MAIN
 int main(){
 	
	read();

	// RANDOM WIDTH ARRAY
	if(diffW>NH/2){
		sizeW = NH-diffW;
		invRandW =1;
		resize_num_BW = -1;
	}
	
	int *rand_arrayW;
 	rand_arrayW = Create_Random_Array_W(sizeW,0,100);

	// RANDOM HIGHT ARRAY 	
	if(diffH>NV/2){
		sizeH = NV-diffH;
		invRandH =1;
		resize_num_BH = -1;
	}
	
 	int *rand_arrayH;
 	rand_arrayH = Create_Random_Array_W(sizeH,0,100);

	// Image Creation
	Create_Image(rand_arrayW,rand_arrayH, resize_num_BW, resize_num_BH);

	write();
	
	printf("End of Code\n");
	
 	return 0;
 	
 }
 

