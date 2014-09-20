//キャラクターに関する構造体
typedef struct{
	int flag;		//フラグ
	int cnt;		//カウンタ
	int bom;		//ボム
	int bcnt;		//残無敵フレーム
	int type;		//自機タイプ
	int img;
	int slow;		//スローかどうか
	int slow_flag;	//低速移動禁止用のフラグ
	double x,y;		//座標
	int graze;		//グレイズ
	double percent;	//段位ゲージ
	int percent_graph[100];//段位ゲージ推移
	int grade;		//合計達成度
}ch_t;

//敵に関する構造体
typedef struct{
	int flag,cnt,img;
	//フラグ、カウンタ
	double x,y,vx,vy,sp,ang;
	//座標、速度x成分、速度y成分、スピード、角度
}enemy_t;

//パッドに関する構造体
typedef struct{
	int key[PAD_MAX];
}pad_t;

//コンフィグに関する構造体
typedef struct{
	int left,up,right,down,shot,bom,slow,start;
}configpad_t;

//弾に関する構造体
typedef struct{
	//フラグ、種類、カウンタ、色、状態、少なくとも消さない時間、エフェクトの種類、グレイズしたか
	int flag,knd,cnt,col,state,till,gflag;
	//座標、角度、速度
	double x,y,vx,vy,angle,spd;
}bullet_t;

//弾の情報
typedef struct{
	int size_x,size_y,col_num,kaiten;
	double range;
}bullet_info_t;

//リプレイ情報
typedef struct{
	int move[4][FLAME_MAX];//十字キー
	int slow[FLAME_MAX];//低速ボタン
	int bom[FLAME_MAX];//ボムボタン
	int rands;//乱数初期値
	int type;//自機タイプ
	int stage;//難易度
}replay_t;