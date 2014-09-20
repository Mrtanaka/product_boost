#include "GV.h"
#include "dirent.h"

//リプレイファイルの保存
void write_replay(){
	DATEDATA replay_date;
	GetDateTime(&replay_date);//時刻の取得
	//ファイル名の設定
	char replay_name[NAME_MAX];
	sprintf(replay_name,"%d%d%d%d%d",replay_date.Mon,replay_date.Day,
		replay_date.Hour,replay_date.Min,replay_date.Sec);
	strcat(replay_name,".rep");

	FILE* fp = fopen(replay_name,"wb");
	fwrite(&replay,sizeof(replay_t),1,fp);
	fclose(fp);
}

//リプレイファイル一覧の取得
void load_replay(){
	memset(replay_list,'\0',sizeof(char)*NAME_MAX);
	char path[] = "./";
	int load_count = 0;

	DIR *dir;
	struct dirent *ds;

	dir = opendir(path);
	
	for(ds=readdir(dir);ds!=NULL;ds=readdir(dir)){
		if(strstr(ds->d_name,".rep") != NULL){
			strcpy(replay_list[load_count],ds->d_name);
			++load_count;
		}
		if(load_count == 10){
			break;
		}
	}
}

//指定したファイルの読み込み
void read_file(char *file_name){
	FILE* fp = fopen(file_name,"r");
	fread(&replay,sizeof(replay_t),1,fp);
}