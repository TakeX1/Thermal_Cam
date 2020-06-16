#include "ofApp.h"
#include "SPI.h"
#include "Lepton_I2C.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//***************************
const int colormap_contrast[] = {16, 16, 16, 23, 16, 22, 30, 15, 30, 37, 16, 37, 46, 15, 45, 53, 15, 52, 60, 15, 60, 67, 15, 67, 75,
                     15, 75, 82, 15, 81, 89, 15, 90, 98, 14, 96, 105, 14, 105, 112, 14, 111, 120, 15, 121, 127, 15, 127,
                     135, 15, 135, 143, 14, 142, 150, 14, 150, 158, 14, 157, 165, 14, 165, 172, 14, 172, 179, 14, 180,
                     186, 14, 187, 195, 14, 195, 202, 14, 201, 209, 14, 210, 217, 14, 216, 209, 15, 214, 202, 14, 211,
                     194, 15, 209, 187, 14, 206, 179, 15, 204, 172, 14, 201, 165, 15, 199, 157, 14, 196, 150, 15, 194,
                     141, 14, 191, 135, 15, 189, 126, 14, 186, 120, 15, 184, 112, 14, 181, 105, 15, 179, 97, 14, 176,
                     91, 15, 174, 82, 14, 171, 74, 15, 169, 67, 14, 166, 60, 15, 164, 52, 14, 161, 45, 15, 159, 38, 14,
                     156, 30, 15, 154, 23, 14, 151, 15, 15, 149, 16, 23, 152, 14, 30, 155, 15, 38, 156, 15, 44, 158, 14,
                     53, 162, 14, 59, 164, 15, 67, 165, 13, 74, 168, 14, 82, 171, 15, 89, 174, 13, 96, 176, 14, 104,
                     178, 14, 111, 180, 13, 119, 183, 13, 125, 185, 14, 133, 187, 12, 140, 189, 13, 148, 192, 14, 155,
                     195, 12, 162, 198, 13, 170, 199, 13, 177, 201, 12, 185, 205, 12, 191, 207, 13, 199, 208, 11, 206,
                     211, 12, 214, 214, 12, 208, 206, 12, 205, 200, 12, 199, 192, 12, 194, 185, 12, 190, 176, 12, 185,
                     169, 14, 181, 162, 12, 176, 155, 13, 170, 147, 14, 166, 141, 13, 161, 133, 13, 156, 125, 14, 151,
                     119, 13, 147, 110, 14, 142, 103, 14, 137, 96, 13, 132, 88, 14, 128, 81, 14, 122, 74, 13, 118, 66,
                     14, 113, 60, 15, 108, 52, 14, 104, 44, 15, 99, 36, 15, 93, 29, 15, 90, 22, 15, 84, 15, 23, 89, 14,
                     28, 93, 13, 36, 97, 15, 42, 103, 14, 49, 106, 13, 55, 112, 13, 63, 116, 12, 69, 120, 13, 76, 125,
                     12, 84, 129, 12, 90, 134, 11, 97, 138, 10, 104, 143, 12, 111, 147, 11, 117, 152, 10, 124, 156, 9,
                     130, 161, 10, 138, 165, 10, 144, 170, 9, 151, 174, 9, 159, 179, 8, 165, 183, 9, 172, 187, 8, 179,
                     193, 8, 186, 196, 7, 192, 202, 6, 200, 206, 8, 205, 210, 7, 213, 215, 6, 209, 208, 7, 207, 201, 7,
                     204, 194, 7, 200, 187, 7, 196, 180, 8, 194, 173, 8, 191, 166, 8, 187, 159, 9, 183, 153, 9, 181,
                     145, 9, 178, 139, 10, 174, 132, 10, 172, 124, 10, 168, 118, 11, 166, 112, 10, 162, 105, 10, 160,
                     98, 11, 156, 91, 11, 153, 84, 11, 150, 77, 12, 147, 70, 12, 143, 63, 12, 140, 57, 13, 137, 49, 13,
                     134, 43, 13, 130, 36, 14, 127, 29, 14, 124, 22, 14, 121, 15, 15, 124, 16, 17, 128, 17, 19, 130, 20,
                     19, 133, 21, 21, 135, 21, 22, 139, 23, 24, 141, 25, 24, 144, 26, 26, 148, 28, 28, 151, 29, 30, 153,
                     31, 30, 156, 32, 32, 160, 34, 34, 163, 35, 36, 164, 36, 36, 168, 38, 38, 171, 39, 40, 174, 40, 42,
                     176, 43, 42, 180, 44, 44, 183, 45, 46, 187, 46, 48, 189, 49, 48, 191, 49, 49, 194, 50, 51, 198, 52,
                     53, 200, 54, 53, 203, 55, 55, 204, 60, 61, 205, 67, 68, 206, 73, 72, 207, 79, 79, 208, 84, 84, 209,
                     91, 91, 210, 96, 97, 211, 103, 104, 212, 109, 108, 213, 115, 114, 214, 120, 120, 215, 127, 127,
                     216, 132, 133, 217, 139, 139, 218, 145, 143, 219, 151, 150, 220, 156, 156, 221, 163, 163, 222, 168,
                     169, 223, 175, 175, 224, 181, 179, 225, 187, 186, 226, 192, 192, 227, 199, 199, 228, 204, 204, 229,
                     211, 211, 230, 217, 215, 231, 223, 222, 232, 228, 228};
const int  *colormap=colormap_contrast;
static uint16_t *frameBuffer;
ofImage img,img1,myImage1;
char Pi3_ip[15];
uint16_t ondox[170][120],ondox_old[170][120];

int    touchX = int(79 % 80), touchY = int(59 / 30) * 60 + int(59 % 30) * 2  + int( 79 / 80);
int    touchXm = int(79 % 80), touchYm = int(59 / 30) * 60 + int(59 % 30) * 2  + int( 79 / 80);
float  sl_256 = 0.0f;
float  value_min = 0, value_max = 0, tempXY  = 0;
float  th_l=999,th_h=999;
float  av3;
int    av5,huri1=0;
double  diff;
bool   ok;
float  ttt,tttx,fpa,ttt1,ttt2,ttt3,ttt4,ttt5;
int     past=0;

int     Lepton_3x,read_err=0,test_err=0,F_H=0;
string  ver,baf1="",baf2="0",baf3="0",baf4="0",baf5="0";
int b_count=0;

float memthermal,mem_mem,mem_fpa;
bool cursol,memplus;
int mem_maxmin;
double hosei;
float time_th;
float hosyaritu=1.0f;
float Ref_Slide=1.0f;
float fp;

struct todo_thermal {
    int thermal9x9X;
    int thermal9x9Y;
    int x;
    int y;
};
struct todo_thermal1 {
    float thermal_X;
    int thermal9x9X;
    int thermal9x9Y;
    int x;
    int y;
};
struct buffer_x {
   uint8_t resultb[164*240];
    
};
buffer_x bufferxx;
todo_thermal xxth;
todo_thermal1 yyth;
std::vector<todo_thermal>thermals;
std::vector<todo_thermal1>thermals1,thermals_m;
std::vector<buffer_x>bufferx;
bool mem_mode,ffc_hosei=false;
int coun_t;
bool ffc_s=false,restart=false,mem_ffc=false;
int col_d,row_d,x_d,y_d;
float thermals_d,ffc_hoseif=0.0f;
int m_count;
//---------LEPTON Reset--------------------------------
void L_reset(){
        tttx=ofGetElapsedTimef();
        SpiClosePort(0);
        usleep(6000); //5000
        SpiOpenPort(0);
        lepton_restart();
        restart=true;
}
//---------Get my IP---------------------------------
int IP_Adr (char *abc) {
struct ifaddrs * ifAddrStruct=NULL;
struct ifaddrs * ifa=NULL;
void * tmpAddrPtr=NULL;
char addressBuffer[INET_ADDRSTRLEN];

    getifaddrs(&ifAddrStruct);
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) {
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            printf("%s IP4 Address %s\n", ifa->ifa_name, addressBuffer);
        }
    }
     for(int ii=0;ii<INET_ADDRSTRLEN;ii++){
           abc[ii]=addressBuffer[ii];
       }
    if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
    return 0;
}
//------------- LEPTON READ -------------------------------------
void R_flame(){
int ecount=0,ecount2=0;
int byte1=164*20;  //164*X
uint8_t result[164*240];

usleep(2000); //usleep(2000); x2600 x2000
baka:    result[3280] = 0;      //164*20=3280
    int ecount1=-1;
    while ((result[3280] & 0b01110000) != 0x10) {    //確実に１セグメント目を捕まえるための処理。２０行目にセグメント番号が出力される。
        uint16_t data = 0x0F;
        while ((data & 0x0f) == 0x0f ) //エラー行を読み飛ばすための処理 セグメントの一番最初の行を捕まえる。0x0fよりこの方が早い
        {
            usleep(68);    //BEST 70    184    60  70  75 60 70
            ecount1++;
            read(spi_cs0_fd, result, sizeof(uint8_t)*164);
            data =  result[0];
            if (ecount1>120){  //900はだめ　　100,120はOK=120
                            usleep(550);  //500
                            ecount2++;
                            baf2=ofToString(ecount2);
                            if (ecount2>50)  //50
                                {
                                    ecount2=0;
                                    read_err++;
                                    baf4=ofToString(read_err);
                                    L_reset();
                                }
                            goto baka;
                            }
        }
        for (int frame_number = 164; frame_number < 9840; frame_number+=byte1) {
            read(spi_cs0_fd, result+sizeof(uint8_t)*frame_number, sizeof(uint8_t)*byte1);
        }
    }
    for(int ii = 9840; ii < 39360; ii+=9840){
        usleep(6060);  // BEST!!6070  x6100

        for(int i = ii; i < ii+9840; i+=byte1){
            read(spi_cs0_fd, result+sizeof(uint8_t)*i, sizeof(uint8_t)*byte1);
        }
    }
    int ii=0;
    //ここはエラーが出なくなったので実行しなくても良いが取るとリセット倍増
    for (int i= 0;i<39360;i+=164)
    {
        if (result[i+1] != ii) {
                ecount ++;
                if(ecount>10){
                    L_reset();
                    test_err++;
                    baf5=ofToString(test_err);
                    ecount=0;
                }
                baf3=ofToString(ecount);
                ecount2=0;
                goto baka;
        }
        ii++;
        if (ii==60) ii=0;
    }
    //LEPTON Rawを　バッファに保存
    memcpy(bufferxx.resultb,result,sizeof(result));
    bufferx.emplace_back(bufferxx);
}
//--------------------------------------------------------------
float l35(float raw_new){
    return 0.01f *(float)raw_new-273.152519f;
}
//--------------------------------------------------------------
void Lepton_ffc(){
     lepton_ffc_start();  //ffc実行
     lepton_hosya(hosyaritu);
     usleep(1000000/8.6*8);  //ffcリセット後11フレームの時間で正確な値が出る  11 10ほぼok
     bufferx.erase(bufferx.begin(),bufferx.end()); //バッファを空にする
}
//--------------------------------------------------------------
void read_lepton(){
   
    uint8_t result[164*240];
    int row, column;
    uint16_t value,value1;
    uint16_t minValue = 65535,minValue_old;
    uint16_t maxValue = 0,maxValue_old;
    int tempXY1,tempXY1_old;
    int col1,row1,colm,rowm;
    float heikin_kizyun;
    int ondosa;
    int max_min,max_min_old;
    //バッファ確認
redo:    while(bufferx.size() < 1)  usleep(100);  //R_flameより実行サイクルが早いのでバッファに１個貯まるまでウエイトさせる
                                                  //１個以上だとかなりの遅延発生
    memcpy(result,bufferx[0].resultb,sizeof(bufferx[0].resultb)); //1画面読み込み
    bufferx.erase(bufferx.begin());//読み込んだら先頭の画像データを削除
    frameBuffer = (uint16_t *)result; //ポインタだけなのでスピード問題なし
    //配列に変換
    for(int i=0;i<19680;i++) {
        if(i % 82 < 2) {
            continue;
        }
        int temp = result[i*2];
        result[i*2] = result[i*2+1];
        result[i*2+1] = temp;
    }
    //まず　読み込んだRAWを配列に直し、カーソルポイントの座標の行列番号を記憶させる
    int tx=touchY * 164 + 2 * (touchX+2) ;
    int txm ;
    if (cursol) txm=touchYm * 164 + 2 * (touchXm+2);
    else        txm=tx;
    for(int k=0; k<19680; k++) {
        if  (k % 82 < 2)        continue;
        value = (int)frameBuffer[k];
        if      (value>255)     value=255;
        else if (value<0)       value=0;
        if((k/82) % 2 == 0){
                column = (k % 82 - 2);
                row = (k / 82)/2;
        }
        else{
                column = ((k % 82 - 2))+(82-2);
                row = (k / 82)/2;
        }
        ondox[column][row]     =(int)frameBuffer[k];
        
        if   ( cursol && k*2==txm )     { colm=column; rowm=row;}
        if   ( k*2==tx )                { col1=column; row1=row;}
    }
    //カーソルポイント5X5 平均値を求める
    if((colm<0 || colm >160) || (rowm<0 || rowm>160)) goto start; //リードエラー対策
    if(cursol){         //基準温度指定部分5x5の平均値を出す
        if( mem_ffc){    //メモリーモード最初の温度がほぼ正しいのでFFCリセット後12コマ待ってRAW配置をコピー。この場所でなきゃ無い
            mem_ffc=false;
            memcpy(ondox_old,ondox,sizeof(ondox));  //FFC時点の画像RAWを配列にコピー
        }
      // 一応エラー対策
        int x1=colm-2;    if(x1<0    )     x1=0;
        int x2=colm+2;    if(x2>160)     x2=160;
        int y1=rowm-2;    if(y1<0    )     y1=0;
        int y2=rowm+2;    if(y2>120)     y2=120;
        int max=0,max1=0;
        for(int i=x1;i<=x2;i++)
        {
            for (int j=y1;j<=y2;j++){
                max=ondox[i][j]+max;
                max1=ondox_old[i][j]+max1;
            }
        }
        max_min=max/25.0f;
        max_min_old=max1/25.0f;
        
        //メモリモードの場合。M+ボタンを押した後の処理。直前のmem_mem が基準となる
        if(memplus) {
           if(mem_mode==false ) //最初にメモリーモードになったときの処理
           {
               Lepton_ffc();  //FFC直後の信頼できる画像データがondox_old配列に入ってくる
               mem_mode=true;
               restart=false;
               mem_ffc=true;
               printf("MEM_MODE FFC Reset!!\n");
               goto redo;  //再度平均計算
           }
            
            mem_mem=max_min_old; //基準値は常にFFC直後の温度（観察による一番正しい数値）
            
            if(Ref_Slide > 0) mem_mem=(Ref_Slide+273.152519)*100.0f;//スライダーが調整されたときの処理
            ondosa=mem_mem-max_min;
            hosei=mem_mem/max_min;
            for (int i=0 ;i<160;i++){
                for(int j=0;j<120;j++){
                    
                    ondox[i][j]=(double)ondox[i][j]*hosei;
                }
            }
            // 補正してから再度平均値計算
            int max=0;
            for(int i=x1;i<=x2;i++)
            {
                for (int j=y1;j<=y2;j++){
                    max=ondox[i][j]+max;
                }
            }
            memthermal=max/25.0f;
            memthermal=l35(memthermal)+ffc_hoseif;
        }
        else {   //メモリーモードでない場合
            memthermal=max_min; //
            memthermal=l35(memthermal)+ffc_hoseif;
            mem_mode=false;
        }
    } //カーソルモード処理終了
//*****************補正後以下所用部分の温度計算実行*********************
start: if( restart) //リセットしたときの処理
        {
            Lepton_ffc();
            mem_mode=true;
            restart=false;
        }
        fpa=lepton_temperature();

    //最大最小値を求める
    for (int i=0 ;i<160;i++){
        for(int j=0;j<120;j++){
            value = ondox[i][j];value1 = ondox_old[i][j];
            if(value> maxValue) {
                maxValue = value;
            }
            if(value < minValue) {
                if(value != 0)
                   minValue = value;
            }
        }
    }
    //カーソルポイント3x3の平均値を求める。直後の温度をコンソールに表示させるため一応ondx_oldも計算させる
    int txy=0,txy1=0;
    for (int i=-1;i<2;i++){
        for(int j=-1;j<2;j++){
                txy=ondox[col1+i][row1+j]+txy;
                txy1=ondox_old[col1+i][row1+j]+txy1;
            }
        }
    tempXY1=txy/9.0f;
    tempXY1_old=txy1/9.0f;

    if(ofGetElapsedTimef()-ttt1 > 0.1) {
        lepton_hosya(hosyaritu);  //放射率他変更 0.1秒おきに修正
        int damy= lepton_ffc_status(); //ffcが起こったかどうかの判定これ入れないとFFC後温度が狂う
        if (damy==1) {ffc_s=true;}
        if( (ffc_s && damy==0) ||tempXY1_old<-100) {
            ffc_hosei=true;ffc_hoseif=-0.1f;
            ffc_s=false;
            ttt5=ofGetElapsedTimef();
        }
        ttt1=ofGetElapsedTimef();
    }
    if(ffc_hosei){
        if(ofGetElapsedTimef()-ttt5>5.0f){
            ffc_hosei=false;ffc_hoseif=0.0f;
            printf("Hosei END!!\n");

        }
    }
    double rrr = (double)(maxValue - minValue) * (1.0f - abs(sl_256)); //高温側を256等分 iPhoneスライダーに連動 標準は0。最高で0.9
        
    diff = rrr / 256.0f;
    if(diff < 1.0f) diff = 1.0f;  //256階調で表現できなくなったらノイズを減らすため強制的に256階調演算をさせる
    rrr = (double)(maxValue - minValue) * sl_256;         //開始低温度側温度
    if (sl_256 > 0) minValue = (double)minValue + rrr; //最低温度表示も開始温度に連動させる
    if (sl_256 < 0) maxValue = (double)maxValue + rrr; //最高温度表示も開始温度に連動させる minはそのまま
    value_min = l35(minValue)+ffc_hoseif;
    value_max = l35(maxValue)+ffc_hoseif;
    tempXY    = l35(tempXY1)+ffc_hoseif;
    if(abs(ondosa/100.0)>6.0 && memplus) memthermal=999;   //標準設定部分が5℃以上違っていたら９９９を送る Lepton3.5のみ
    if(th_l != 999){   //　温度範囲指定の時の事前計算
            double   av1=256.0f/(th_h-th_l);
                    av3=av1/(256.0f/(value_max-value_min));
                    av5=int((value_min-th_l)*av1);
            }
    else {av3=1; av5=0;}   //iPhoneから送られてくる温度差が0以下なら通常の色設定にする
    double avx=av3/diff;
    double avxx=-minValue*avx+av5;
    //PI用の画面表示前処理
    for (int i=0 ;i<160;i++){
           for(int j=0;j<120;j++){
               value = (double)ondox[i][j]*avx+avxx;
               if(value>255) value=255;
               else if(value<0) value=0;
               img.setColor(i, j, value);
           }
    }
      //AI のTo-Do機能により送られて来る座標中心16x32ポイントの最高温度を算出（iPhoneに送る）顔の場合はマスク使用の可能性があるため
    if(thermals.size()>0){
          for(int t=0;t<thermals.size();t++){
              int col2=thermals[t].thermal9x9X;
              int row2=thermals[t].thermal9x9Y;
              int x1=col2-8;    if(x1<0    )     x1=0;
              int x2=col2+8;    if(x2>160)     x2=160;
              int y1=row2-16;    if(y1<0    )     y1=0;
              int y2=row2+16;    if(y2>120)     y2=120;
              float max_min1=0;
              for(int i=x1;i<=x2;i++)
              {
                  for (int j=y1;j<=y2;j++){
                      float max_1=(float)ondox[i][j];
                      //float max_2=(float)ondox_old[i][j];
                      if (max_1 >max_min1) {max_min1=max_1;}
                  }
              }
              max_min1=l35(max_min1)+ffc_hoseif;
              
              yyth.thermal_X=max_min1;
              yyth.thermal9x9X=col2;
              yyth.thermal9x9Y=row2;
              yyth.x=thermals[t].x;
              yyth.y=thermals[t].y;
              thermals1.emplace_back(yyth);
          }
          thermals.clear();
      }
}

//--------------LEPTON読み込みスレッド--------------------------------
class Xxlepton:public ofThread{
public:
private:
  void threadedFunction(){
      float timex;
      while(1){
        R_flame();
        }
  }
};
Xxlepton ll;
//----------------温度、画像変換スレッド--------------------------------
class Xxlepton1:public ofThread{
public:
private:
  void threadedFunction(){
      float timex;
      while(1){
        read_lepton();
        }
  }
};
Xxlepton1 ll1;
//--------------------------------------------------------------
void ofApp::setup(){

    Lepton_3x=lepton_no();  //1=V3.5  2=V3.0 0=none;
    if(Lepton_3x==1) ver="3.5";
    else ver="3.0";
    baf1="It's 0 minits Past!!";
    
    font.load("verdana.ttf", 20, true, true, true);
    font1.load("verdana.ttf", 30, true, true, true);
    myImage1.load("WTlogoH.png");
    ofSetFrameRate(30); // run at 20fps 大きすぎるとiPhone側オーバーフローぎみ
    ofSetVerticalSync(true);
    HOST=arg_x;
    sender.setup(HOST, SPORT);
    receiver.setup( RPORT );
    img.allocate(160,120,OF_IMAGE_GRAYSCALE);
    img1.allocate(160,120,OF_IMAGE_COLOR);
    IP_Adr(Pi3_ip);printf("Pi3 IP= %s\n",Pi3_ip);
    
    SpiOpenPort(0);
    usleep(10000);
    ttt=ofGetElapsedTimef();
    tttx=ofGetElapsedTimef();
    ttt1=ofGetElapsedTimef();
    for(int i=0;i<160;i++){
        for (int j=0;j<120;j++){
            img.setColor(i, j, 0);
        }
    }
    ll.startThread();   //LEPTON読み込みタスク開始。２つのタスクはバッファで通信させている
    ll1.startThread();  //RAWデータ変換タスク開始

    if(Lepton_3x != 1){
        fpa=lepton_temperature();  // if LEPTON3.0
    }
    mem_mode=true;
    restart=true;
}
//--------------------------------------------------------------
void ofApp::update(){
    if(ofGetElapsedTimef()-ttt > 60) {
                        ttt=ofGetElapsedTimef();
                        past++;
                        baf1=ofToString(past)+" minits Past!!";
                        baf2="0";
                        baf3="0";
                        //for LEPTON3.5
                        if(Lepton_3x != 1){
                            fpa=lepton_temperature();
                        }
    }
    img.update();
    
    unsigned char *data1;
    int xxx;
    //OSC 送受信処理
    ofxOscMessage my1;  //画像データをBlobに変換して送る char型にすると内部変換が行われないため早い
                        //LEPTON程度の画像ならデータを分けて送らなくてもOK
    data1=img.getPixels().getData();
    my1.setAddress("/i");
    ofBuffer buffer((char *)data1, 19200);
    my1.addBlobArg(buffer);
    sender.sendMessage(my1);
    usleep(10000);  //かなり重要
    
    while( receiver.hasWaitingMessages() ){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        string GM=m.getAddress() ;
        //*********Resive Point & Config
        if(GM == "/t" ){   //カーソル位置などの受信処理
        //    cursol=false;memplus=false; //これがあると通信が詰まったとき誤動作が入る可能性がある。メモリーが書き換わる？
            touchX  = m.getArgAsInt(0);         //標準画面でのカーソル位置
            touchY  = m.getArgAsInt(1);
            sl_256  = m.getArgAsFloat(2);       //Dynamic range
            F_H        = m.getArgAsInt(3);      //Sayu Hanten
            th_l    = m.getArgAsFloat(4);       //Color renge
            th_h    = m.getArgAsFloat(5);
            hosyaritu = m.getArgAsFloat(6);     //放射率
            cursol  = m.getArgAsBool(7);        //基準位置測定モードか、そうでないか
            memplus = m.getArgAsBool(8);        //メモリーモードかそうでないか
            touchXm  = m.getArgAsInt(9);        //メモリーモードの場合の基準対象物の位置
            touchYm  = m.getArgAsInt(10);
            Ref_Slide= m.getArgAsFloat(11);     //メモリーモードの場合の設定温度
         }
        else if(GM == "/u" ){   //AIで認識した複数ボックスの中心（複数受付）
           //thermals1.clear();
           coun_t  = m.getArgAsInt(0);
           for(int t=0;t<coun_t;t++){
               xxth.thermal9x9X=    m.getArgAsInt(t*4+1);
               xxth.thermal9x9Y=    m.getArgAsInt(t*4+2);
               xxth.x=              m.getArgAsInt(t*4+3);
               xxth.y=              m.getArgAsInt(t*4+4);
               
               thermals.emplace_back(xxth);
           }
        }
         //********Resive Lepton reset
         else if(GM == "/r" ){
                SpiClosePort(0);
                int sss=m.getArgAsInt(0);
                if (sss==1){
                    usleep(5000);
                    SpiOpenPort(0);
                    lepton_restart();
                }
            }
        }
        //*******測定温度類を送る
        ofxOscMessage mm;
            mm.setAddress("/m");
            mm.addFloatArg(value_min);  //最高温度
            mm.addFloatArg(value_max);  //最低温度
            mm.addFloatArg(tempXY);     //カーソル位置温度（iPhone伸使用場面により使い方が違うので注意)
            mm.addStringArg(Pi3_ip);    //PIのIPアドレスを送る
            mm.addFloatArg(memthermal); //確認用に基準対象物の温度を送る
            sender.sendMessage(mm);
    
       if(thermals1.size()>0){  //iPhoneのバウンデイングボックスの中心位置とその中の最高温度を送る
           ofxOscMessage my;
           my.setAddress("/v");
           thermals_m.resize(thermals1.size());
           copy(thermals1.begin(), thermals1.end(), thermals_m.begin() ); //Vector コピー
           my.addIntArg(thermals1.size());
           for(int t=0;t<thermals1.size();t++){
               my.addFloatArg(thermals1[t].thermal_X);
               my.addIntArg(thermals1[t].thermal9x9X);
               my.addIntArg(thermals1[t].thermal9x9Y);
               my.addIntArg(thermals1[t].x);
               my.addIntArg(thermals1[t].y);
           }
           sender.sendMessage(my);
           thermals1.clear();
          
       }
}
//--------------------------------------------------------------
void ofApp::draw(){
    //int y_count;
    m_count++;
    if(m_count>20 && thermals_m.size()>0){  //温度表示のちらつき防止
        thermals_m.clear();
        m_count=0;
    }
    ofBackgroundGradient(0, 0);
    img1.update();
    unsigned char *idata;
            idata=img.getPixels().getData();
    for(int i=0;i<160;i++){
                for (int j=0;j<120;j++){
                       int vv=int(idata[i+j*160]*0.875)*3;
                        img1.setColor(160-i, j, ofColor(colormap[vv],colormap[vv+1],colormap[vv+2],100));
                }
        }
    img1.draw(25,25,900,600);
    
    ofColor(255,255,255);
    // display instructions
    string buf = "sending osc to: " + string(HOST);
    buf += " " + ofToString(SPORT)+" LEPTON "+ver;
    //ofDrawBitmapStringHighlight(buf, 10, 20);
    font.drawString(buf, 120,20);
    font.drawString(baf1,930,50);
    
    ofSetColor(180,180,180);
    font.drawString(baf1,930,50);
    font.drawString("Read error---> "+baf2,930,74);
    font.drawString("Error flame--> "+baf3,930,96);
    font.drawString("Reading Reset: "+baf4,930,118);
    font.drawString("Testing Reset : "+baf5,930,140);
    
    myImage1.draw(935,550,190,72);  //w&t logo
    ofSetColor( 255,255,255);
    //メモリー部分の温度表示
    float baix=900.0f/160.0f,baiy=600.0f/120.0f;
    if(thermals_m.size()>0){
        ofColor(255,255,255);
        for(int t=0;t<thermals_m.size();t++){
            ofDrawCircle(25+(160-thermals_m[t].thermal9x9X)*baix,25+thermals_m[t].thermal9x9Y*baiy,12);
            string buf =ofToString(thermals1[t].thermal_X,1)+"°C";
            font1.drawString(buf, 25+(160-thermals_m[t].thermal9x9X)*baix+10,25+thermals_m[t].thermal9x9Y*baiy-10);
        }
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
