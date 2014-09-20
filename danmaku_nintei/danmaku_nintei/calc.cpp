#include "GV.h"

//メニュー数を指定し、選択制御
void calc_menu(int menu){
	int up = CheckStatePad(configpad.up), down = CheckStatePad(configpad.down);

	if(up == 1 || (up >= 60 && up % 10 == 0)){
		if(menu_state > 0) menu_state--;
		else menu_state = menu-1;//選択メニューを上へ
	}

	if(down == 1 || (down >= 60 && down % 10 == 0)){
		if(menu_state < menu-1) menu_state++;
		else menu_state = 0;//選択メニューを下へ
	}
}

void calc_main(){//ゲーム中の制御
	if(CheckStatePad(configpad.start) == 1){
		se_flag[3] = 1;
		func_state = 2;//ポーズ
	}
}

pad_t padc;//キーコンshotボタン誤変更防止のためのキー情報格納変数
void calc_title(){//タイトル画面の制御
	calc_menu(5);

	if(CheckStatePad(configpad.shot) == 1){
		switch(menu_state){
		case 0://難易度選択へ
			menu_state = 0;
			se_flag[3]=1;
			func_state = 7;
			break;
		case 1://リプレイファイル選択へ
			menu_state = 0;
			se_flag[3]=1;
			func_state = 11;
			break;
		case 2://キーコンフィグへ
			menu_state = 0;
			se_flag[3]=1;
			padc.key[configpad.shot] = 2;//shot押下フレームを2にしてshotボタン即変更の防止
			func_state = 5;
			break;
		case 3://マニュアルへ
			menu_state = 0;
			se_flag[3]=1;
			func_state = 6;
			break;
		case 4://ゲーム終了
			menu_state = 0;
			se_flag[3]=1;
			shut_flag = 1;//ゲームシャットダウンフラグ立て
			break;
		}
	}
}

void calc_pause(){//ポーズメニューの制御
	calc_menu(3);

	if(CheckStatePad(configpad.shot) == 1){
		switch(menu_state){
		case 0://ポーズ解除
			menu_state = 0;
			se_flag[3] = 1;
			func_state = 10;
			break;
		case 1://タイトルへ戻る
			menu_state = 0;
			se_flag[3] = 1;
			replay_flag = 0;
			func_state = 1;
			break;
		case 2://リトライ
			menu_state = 0;
			se_flag[3] = 1;
			func_state = 9;
			break;
		}
	}
}

void calc_result(){
	if(count == 120 || count == 180 || count == 240 || count == 300)
		se_flag[3] = 1;

	if(count >= 330){
		calc_menu(4);

		if(CheckStatePad(configpad.shot) == 1){
			switch(menu_state){
			case 0://リトライ
				menu_state = 0;
				se_flag[3]=1;
				func_state = 9;
				break;
			case 1://リプレイ
				menu_state = 0;
				se_flag[3]=1;
				replay_flag = 1;
				func_state = 9;
				break;
			case 2://リプレイ保存してタイトル
				menu_state = 0;
				se_flag[3]=1;
				write_replay();
				replay_flag = 0;
				func_state = 1;
				break;
			case 3://リプレイ保存せずタイトル
				menu_state = 0;
				se_flag[3]=1;
				replay_flag = 0;
				func_state = 1;
				break;
			}
		}
	}
}

void calc_difficult(){
	calc_menu(4);

	if(CheckStatePad(configpad.bom) == 1){
		menu_state = 0;
		func_state = 1;
	}
	else if((CheckStateKey(KEY_INPUT_L) >= 60) && (CheckStateKey(KEY_INPUT_R) >= 60)){
		stage = 4;
		menu_state = 0;
		se_flag[3] = 1;
		func_state = 8;
	}
	else if(CheckStatePad(configpad.shot) == 1){
		stage = menu_state;
		menu_state = 0;
		se_flag[3] = 1;
		func_state = 8;
	}
}

void calc_type(){
	calc_menu(3);

	if(CheckStatePad(configpad.bom) == 1){
		menu_state = 0;
		func_state = 7;
	}
	else if(CheckStatePad(configpad.shot) == 1){
		type = menu_state;
		menu_state = 0;
		se_flag[3] = 1;
		func_state = 9;
	}
}

void calc_key(){
	calc_menu(5);

	int i,PadInput,mul=1;
	PadInput = GetJoypadInputState( DX_INPUT_PAD1 );//パッドの入力状態を取得
	for(i=0;i<16;i++){
		if(PadInput & mul)	padc.key[i]++;
		else				padc.key[i]=0;
		mul*=2;
	}

	for(int i=4;i<PAD_MAX;i++){
		if(padc.key[i] == 1){
			se_flag[3]=1;

			switch(menu_state){
				case 0:
					configpad.shot=i;
					break;
				case 1:
					configpad.bom=i;
					break;
				case 2:
					configpad.slow=i;
					break;
				case 3:
					configpad.start=i;
					break;
			}
		}
	}

	if((menu_state==4) && (CheckStatePad(configpad.shot) == 1)){
		menu_state=0;
		se_flag[3]=1;
		func_state=1;
	}
}

void calc_manual(){
	calc_menu(7);

	if(CheckStatePad(configpad.bom) == 1){
		menu_state = 0;
		func_state = 1;
	}
}

void calc_choosefile(){
	int file_number = 0;
	load_replay();

	for(int i = 0; replay_list[i][0] != '\0';i++){
		++file_number;
	}

	if(file_number != 0){
		calc_menu(file_number);
	}
	if(CheckStatePad(configpad.bom) == 1){
		menu_state = 0;
		func_state = 1;
	}

	else if(CheckStatePad(configpad.shot) == 1 && file_number != 0){
		menu_state = 0;
		se_flag[3] = 1;
		read_file(replay_list[menu_state]);
		replay_flag = 1;
		func_state = 9;
	}
}