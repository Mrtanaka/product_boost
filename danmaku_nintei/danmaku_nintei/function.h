//enemy.cpp
	GLOBAL void enemy_main();

//chara.cpp
	GLOBAL void ch_main();

//fps.cpp
	GLOBAL void fps_wait();
	GLOBAL void draw_fps(int x, int y);

//graph.cpp
	GLOBAL void graph_main();
	GLOBAL void graph_title();
	GLOBAL void graph_pause();
	GLOBAL void graph_result();
	GLOBAL void graph_difficult();
	GLOBAL void graph_type();
	GLOBAL void graph_key();
	GLOBAL void graph_manual();
	GLOBAL void graph_choosefile();

//calc.cpp
	GLOBAL void calc_main();
	GLOBAL void calc_title();
	GLOBAL void calc_pause();	
	GLOBAL void calc_result();
	GLOBAL void calc_difficult();
	GLOBAL void calc_type();
	GLOBAL void calc_key();
	GLOBAL void calc_manual();
	GLOBAL void calc_choosefile();

//ini.cpp
	GLOBAL void first_ini();
	GLOBAL void ini();

//shot.cpp
	GLOBAL double shotatan2();
	GLOBAL double rang(double);
	GLOBAL int shot_search();
	GLOBAL void shot_main();
	GLOBAL void bdelete();

//key.cpp
	//現在のキー入力処理を行う
	GLOBAL int GetHitKeyStateAll_2();
	//受け取ったキー番号の現在の入力状態を返す
	GLOBAL int CheckStateKey(unsigned char Handle);

	//現在のパッド入力処理を行う関数
	GLOBAL void GetHitPadStateAll();
	//受け取ったパッド番号の現在の入力状態を返す
	GLOBAL int CheckStatePad(unsigned int Handle);

//laod.cpp
	//データのロード
	GLOBAL void load();

//music.cpp
	GLOBAL void music_ini();
	GLOBAL void music_play();

//out.cpp
	GLOBAL void out_main();

//file.cpp
	GLOBAL void write_replay();
	GLOBAL void load_replay();
	GLOBAL void read_file(char *file_name);