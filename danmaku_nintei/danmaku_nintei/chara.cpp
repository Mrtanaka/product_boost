#include "GV.h"

void calc_ch(){
    ch.cnt++;//キャラクタカウントアップ
    ch.img=(ch.cnt%24)/6;//現在の画像決定
}

void calc_percent(){
	if(ch.percent > 100.0)//ゲージは100%を超えない
		ch.percent = 100.0;
	if(ch.percent < 0){//ゲージが尽きた場合の処理
		ch.percent = 0;

		bdelete();//全ての弾を消す
		ch.flag=0;//自機を消す
		enemy.flag=0;//敵を消す

		se_flag[7] = 1;
		scount = count;
		count = 0;

		//リプレイ再生なら、演出スキップ
		if(replay_flag == 1){
			count = 300;
		}
		func_state = 4;//ゲームオーバー画面へ
	}
}

//合計達成度の計算
void calc_grade(){
	if(ch.grade==100){
		ch.percent_graph[99] = ch.percent;
	}else{
		//途中経過を保存
		ch.percent_graph[ch.grade] = int(ch.percent);
	}
	ch.grade = (count*100)/19800;

	if(ch.grade == 100){
		if(spell_flag == 0){
			spell++;
		}
		se_flag[6] = 1;
		count = 0;
		//リプレイ再生なら、演出スキップ
		if(replay_flag == 1){
			count = 300;
		}
		func_state = 3;
	}
}

void ch_move(){
    int i,sayu_flag=0,joge_flag=0;
    double x,y,mx,my,naname=1;
    double move_x[4]={-4.0,4.0,0,0},move_y[4]={0,0,4.0,-4.0};
    int inputpad[4],inputslow,inputbom;
    inputpad[0]=CheckStatePad(configpad.left); inputpad[1]=CheckStatePad(configpad.right);
    inputpad[2]=CheckStatePad(configpad.down); inputpad[3]=CheckStatePad(configpad.up);
	inputslow=CheckStatePad(configpad.slow);
	inputbom=CheckStatePad(configpad.bom);

	//リプレイ再生なら、操作をリプレイから取得
	if(replay_flag == 1){
		for(int i = 0;i < 4;i++){
			inputpad[i] = replay.move[i][count];
		}
		inputslow = replay.slow[count];
		inputbom = replay.bom[count];
	}else{//リプレイ再生でないなら、リプレイに記録
		for(int i = 0;i < 4;i++){
			replay.move[i][count] = inputpad[i];
		}
		replay.slow[count] = inputslow;
		replay.bom[count] = inputbom;
	}

	//ボム処理
	if(inputbom==1 && ch.bom > 0){
		ch.bcnt = 60; //ボム効果時間
		--ch.bom;
		se_flag[5]=1;
	}

    if(inputpad[0]>0)//左キーが押されていたら
        ch.img+=4*2;//画像を左向きに
    else if(inputpad[1]>0)//右キーが押されていたら
        ch.img+=4*1;//画像を右向きに

    for(i=0;i<2;i++)//左右分
        if(inputpad[i]>0)//左右どちらかの入力があれば
            sayu_flag=1;//左右入力フラグを立てる
    for(i=2;i<4;i++)//上下分
        if(inputpad[i]>0)//上下どちらかの入力があれば
            joge_flag=1;//上下入力フラグを立てる
    if(sayu_flag==1 && joge_flag==1)//左右、上下両方の入力があれば斜めだと言う事
        naname=sqrt(2.0);//移動スピードを1/ルート2に

    for(int i=0;i<4;i++){//4方向分ループ
        if(inputpad[i]>0){//i方向のキーボード、パッドどちらかの入力があれば
            x=ch.x , y=ch.y;//今の座標をとりあえずx,yに格納
            mx=move_x[i];    my=move_y[i];//移動分をmx,myに代入
            if(inputslow>0 && ch.slow_flag==0){//低速移動なら
                mx=move_x[i]/3;    my=move_y[i]/3;//移動スピードを1/3に
            }
            x+=mx/naname , y+=my/naname;//今の座標と移動分を足す
            if(!(x<FX+10 || x>FX+FMX-10 || y<FY+10 || y>FY+FMY-10)){//計算結果移動可能範囲内なら
                ch.x=x , ch.y=y;//実際に移動させる
            }
        }
    }

	//無敵カウント減少
	if(ch.bcnt){
		ch.bcnt--;
	}
}

void ch_main(){
	calc_ch();
	calc_percent();
	calc_grade();
	ch_move();
}