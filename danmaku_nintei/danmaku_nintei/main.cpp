#define GLOBAL_INSTANCE 
#include "GV.h"

//ループで必ず行う３大処理
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//プロセス処理がエラーなら-1を返す
	if(ClearDrawScreen()!=0)return -1;//画面クリア処理がエラーなら-1を返す
	GetHitKeyStateAll_2();//現在のキー入力処理を行う
	GetHitPadStateAll();  //現在のパッド入力処理を行う
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	ChangeWindowMode(TRUE);//ウィンドウモード
	SetMainWindowText("弾幕段位認定ver1.10");//ウインドウ表示名
	if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//初期化と裏画面化

	while(ProcessLoop()==0){//メインループ
		music_ini();
		switch(func_state){
			case 0://初回のみ入る処理
				load();		//データロード
				first_ini();//初回の初期化
				func_state=1;
				break;
			case 1://タイトル＆モードセレクト
				graph_title();
				calc_title();
				break;
			case 2://ポーズ画面
				calc_pause();
				graph_pause();
				break;
			case 3://リザルト画面
				calc_result();
				graph_result();
				count++;
				break;
			case 4://ゲームオーバー画面
				calc_result();
				graph_result();
				count++;
				break;
			case 5://キーコンフィグ
				calc_key();
				graph_key();
				break;
			case 6://マニュアル
				calc_manual();
				graph_manual();
				break;
			case 7://難易度の選択
				graph_difficult();
				calc_difficult();
				break;
			case 8://自機タイプの選択
				graph_type();
				calc_type();
				break;
			case 9://各種データの初期化
				ini();
				func_state=10;
				break;
			case 10://通常処理
				calc_main();
				ch_main();
				enemy_main();
				shot_main();
				out_main();
				graph_main();
				count++;
				break;
			case 11://リプレイ読み込み
				calc_choosefile();
				graph_choosefile();
				break;
			default:
				printfDx("不明なfunc_state\n");
				break;
		}
		music_play();
		fps_wait();
		if(shut_flag == 1)break;//終了動作があったらブレイク
		ScreenFlip();//裏画面反映
	}
	DxLib_End();//ＤＸライブラリ終了処理
	return 0;
}
