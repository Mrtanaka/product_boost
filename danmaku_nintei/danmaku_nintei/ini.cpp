#include "GV.h"

void input_bullet_info(bullet_info_t *binfo,int size_x,int size_y,int col_num,double range,int kaiten){
	binfo->size_x =size_x;	binfo->size_y =size_y;
	binfo->col_num=col_num;	binfo->range  =range;
	binfo->kaiten=kaiten;
}

//一番最初の初期化
void first_ini(){
	configpad.down=0;
	configpad.left=1;
	configpad.right=2;
	configpad.up=3;
	configpad.bom=6;
	configpad.shot=7;
	configpad.slow=8;
	configpad.start=12;

	input_bullet_info(&bullet_info[0],76, 76, 5,17.0,0);
	input_bullet_info(&bullet_info[1],22, 22, 6, 4.0,0);
	input_bullet_info(&bullet_info[2], 5,120,10, 2.5,0);
	input_bullet_info(&bullet_info[3],19, 34, 5, 2.0,0);
	input_bullet_info(&bullet_info[4],38, 38,10, 2.0,0);
	input_bullet_info(&bullet_info[5],14, 16, 3, 3.5,0);
	input_bullet_info(&bullet_info[6],14, 18, 3, 2.0,0);
	input_bullet_info(&bullet_info[7],16, 16, 9, 2.5,1);
	input_bullet_info(&bullet_info[8],12, 18,10, 1.5,0);
	input_bullet_info(&bullet_info[9],13, 19, 3, 2.0,0);
	input_bullet_info(&bullet_info[10],8,  8, 8, 1.0,0);
	input_bullet_info(&bullet_info[11],35,32, 8, 2.0,0);

	winflag=0;
}

//ゲームの初期化
void ini(){
	count=0;
	memset(&ch,0,sizeof(ch_t));
	memset(&enemy,0,sizeof(enemy_t));
	memset(&bullet,0,sizeof(bullet_t)*BULLET_MAX);
	//リプレイ再生でないならリプレイ内容を初期化
	if(replay_flag == 0){
		memset(&replay,0,sizeof(replay_t));
		replay.rands = GetNowCount();
	}else{
		stage = replay.stage;
		type = replay.type;
	}
	
	SRand(replay.rands);//乱数設定
	

	spell = 0;
	spell_flag = 0;
	spcount=0;
	sg_flag=0;

	ch.x=FX+(FMX/2);
	ch.y=FY+((FMY*3)/4);
	ch.graze = 0;
	ch.percent=100.0;
	ch.grade = 0;
	ch.bom=3;
	
	for(int i = 0;i < 100;i++){
		ch.percent_graph[i] = 0;
	}

	enemy.x=FX+(FMX/2);
	enemy.y=FY+(FMY/4);
	
	ch.flag=1;
	enemy.flag=1;
}