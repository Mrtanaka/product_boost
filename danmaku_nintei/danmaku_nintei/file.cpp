#include "GV.h"
#include "dirent.h"

//���v���C�t�@�C���̕ۑ�
void write_replay(){
	DATEDATA replay_date;
	GetDateTime(&replay_date);//�����̎擾
	//�t�@�C�����̐ݒ�
	char replay_name[NAME_MAX];
	sprintf(replay_name,"%d%d%d%d%d",replay_date.Mon,replay_date.Day,
		replay_date.Hour,replay_date.Min,replay_date.Sec);
	strcat(replay_name,".rep");

	FILE* fp = fopen(replay_name,"wb");
	fwrite(&replay,sizeof(replay_t),1,fp);
	fclose(fp);
}

//���v���C�t�@�C���ꗗ�̎擾
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

//�w�肵���t�@�C���̓ǂݍ���
void read_file(char *file_name){
	FILE* fp = fopen(file_name,"r");
	fread(&replay,sizeof(replay_t),1,fp);
}