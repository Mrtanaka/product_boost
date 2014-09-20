#define GLOBAL_INSTANCE 
#include "GV.h"


namespace
{

//����̂ݓ��鏈��
void initialize(void)
{
	load(); //�f�[�^���[�h
	first_ini(); //����̏�����
	func_state = 1;
}

//�^�C�g�������[�h�Z���N�g
void mode_select(void)
{
	graph_title();
	calc_title();
}

//�|�[�Y���
void pause(void)
{
	calc_pause();
	graph_pause();
}

//���U���g���
void result(void)
{
	calc_result();
	graph_result();
	++count;
}

//�Q�[���I�[�o�[���
void game_over(void)
{
	calc_result();
	graph_result();
	++count;
}

//�L�[�R���t�B�O
void key_config(void)
{
	calc_key();
	graph_key();
}

//�}�j���A��
void manual(void)
{
	calc_manual();
	graph_manual();
}

//��Փx�̑I��
void difficult_select(void)
{
	graph_difficult();
	calc_difficult();
}

//���@�^�C�v�̑I��
void self_type_select(void)
{
	graph_type();
	calc_type();
}

//�e��f�[�^�̏�����
void data_clear(void)
{
	ini();
	func_state=10;
}

//�ʏ폈��
void main_sequence(void)
{
	calc_main();
	ch_main();
	enemy_main();
	shot_main();
	out_main();
	graph_main();
	++count;
}

typedef void (*sequence)(void);
sequence sequences[] = {
  initialize,
  mode_select,
  pause,
  result,
  game_over,
  key_config,
  manual,
  difficult_select,
  self_type_select,
  data_clear,
  main_sequence
};

} // namespace

//���[�v�ŕK���s���R�又��
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//�v���Z�X�������G���[�Ȃ�-1��Ԃ�
	if(ClearDrawScreen()!=0)return -1;//��ʃN���A�������G���[�Ȃ�-1��Ԃ�
	GetHitKeyStateAll_2();//���݂̃L�[���͏������s��
	GetHitPadStateAll();  //���݂̃p�b�h���͏������s��
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h
	SetMainWindowText("�e���i�ʔF��ver1.10");//�E�C���h�E�\����
	if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//�������Ɨ���ʉ�

	while(ProcessLoop()==0){//���C�����[�v
		music_ini();
		if ((func_state >= 0) && (func_state < sizeof(sequences)/sizeof(sequences[0]))) {
			sequences[func_state]();
		} else {
			printfDx("�s����func_state[%d]\n",
               func_state);
		}
		music_play();
		fps_wait();
		if(shut_flag == 1)break;//�I�����삪��������u���C�N
		ScreenFlip();//����ʔ��f
	}
	DxLib_End();//�c�w���C�u�����I������
	return 0;
}
