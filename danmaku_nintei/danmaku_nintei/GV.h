#include "DxLib.h"
#include "define.h"
#include "math.h"

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern
#endif

#include "function.h"

//画像用変数宣言部
GLOBAL int img_ch[12];	//キャラクタ画像12枚分
GLOBAL int img_enemy[9];	//敵画像9枚分
GLOBAL int img_board[5];	//ボードにつかう画像
GLOBAL int img_bullet[12][10];//弾用画像
GLOBAL int img_etc[5];//その他の画像
GLOBAL int img_num[10];//数字の画像
GLOBAL int img_bom;	//ボム画像ハンドラ

//音楽ファイル用変数宣言部
GLOBAL int sound_se[SE_MAX];

//フラグ・ステータス変数
GLOBAL int func_state,count,menu_state;//関数制御用変数
GLOBAL int scount;	//ゲームオーバー時の達成度計算用
GLOBAL int stage,type;	//難易度、自機タイプ
GLOBAL int spcount;	//スペルごとのカウント用
GLOBAL int winflag;	//ウインドウ・フルスクリーン変更用のフラグ
GLOBAL int se_flag[SE_MAX];			//サウンドフラグ
GLOBAL int shut_flag;				//動作停止用フラグ
GLOBAL int spell_flag;				//スペル取得しているかのフラグ
GLOBAL int sg_flag;					//スペル取得時の表示用フラグ
GLOBAL int spell;					//スペル取得枚数
GLOBAL int replay_flag;				//リプレイ再生かどうか
GLOBAL char replay_list[10][NAME_MAX];//リプレイファイル一覧

//その他の変数
GLOBAL int color[10],font[5];//色 フォント

//構造体変数宣言部
GLOBAL ch_t ch;			//キャラクタデータ宣言
GLOBAL enemy_t enemy;//敵情報
GLOBAL configpad_t configpad;//コンフィグで設定したキー情報
GLOBAL bullet_t bullet[BULLET_MAX];//弾
GLOBAL bullet_info_t bullet_info[12];//弾情報
GLOBAL replay_t replay;//リプレイ情報