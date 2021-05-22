//-------------------------------------------------------//
//      ���`�|�p�������ߏ� created by Eijo Takagi        //
//-------------------------------------------------------//
#include"libOne.h"
void gmain() {
    window(1920, 1080, full);
    //�����ݒ�
    rectMode(CENTER);
    angleMode(DEGREES);
    colorMode(HSV);
    strokeWeight(0);
    ShowCursor(false);
    //�p�����^�\����
    struct PARAM {
    //rect�̍���,rect�̕�,������,��]�W��,�s�����x,�ʓx,��]�X�s�[�h,��]�X�E�B�b�`
        float h, w, divNum, coAngle, alpha, saturation, rotSpeed, rotSw, rotAngle;
    };
    //�����p�����^
    const int numPattern = 10;
    struct PARAM initPattern[numPattern] = {
        121,10,24,0,180,255,0.5f,0,0,
        61,1,1292,2,255,255,0.5f,1,0,
        271,1,2070,-2.5f,180,255,0.5f,1,0,
        351,1.5f,1300,5.0f,180,255,0.26f,1,0,
        161,1.5f,113,-0.5f,255,255,0.3f,1,0,
        1421,1.5f,84,-0.5f,255,255,0.34f,1,0,
        281,1.5f,150,2.5f,255,255,-0.35f,1,0,
        361,1.75f,138,-5.25f,255,255,0.5f,1,0,
        380,1,892,24.25f,255,255,0.5f,1,0,
        750,53.0f,27,6.75f,255,100,0.16f,0,45,
    };
    //�p�����^�̃��[�h
    struct PARAM pattern[numPattern];
    FILE* ifp = 0;
    fopen_s(&ifp, "assets\\pattern.bin", "rb");
    fread(pattern, sizeof(PARAM), numPattern, ifp);
    fclose(ifp);
    struct PARAM param = pattern[0];
    //�p�����^�ȊO�̃f�[�^
    float hue = -180;//���[�̐F
    float bright = 255;//���邳
    int preDivNum = 0;//�����������Ƃ��̕�����������Ă���
    float preW = 0;
    int patternNo = 0;
    int menuSw = 1;//���j���[�\����\��
    while (notQuit) {
        //�p�����^����
        if (isPress(KEY_Q))param.h += 10;
        if (isPress(KEY_A) && param.h > 1)param.h += -10;
        if (isPress(KEY_W))param.w += 0.25f;
        if (isPress(KEY_S) && param.w > 1)param.w += -0.25;
        if (isPress(KEY_E))param.divNum += 1;
        if (isPress(KEY_D) && param.divNum > 2)param.divNum += -1;
        if (isTrigger(KEY_I))param.divNum += 1;
        if (isTrigger(KEY_K) && param.divNum > 2)param.divNum += -1;
        if (isTrigger(KEY_R))param.coAngle += 0.25f;
        if (isTrigger(KEY_F))param.coAngle += -0.25f;
        if (isPress(KEY_T) && param.alpha < 255.0f)param.alpha += 1.0f;
        if (isPress(KEY_G) && param.alpha > 1.0f)param.alpha += -1.0f;
        if (isPress(KEY_Y) && param.saturation < 255.0f)param.saturation += 0.5f;
        if (isPress(KEY_H) && param.saturation > 1.0f)param.saturation += -0.5f;
        if (isPress(KEY_U))param.rotSpeed += 0.01f;
        if (isPress(KEY_J))param.rotSpeed += -0.01f;
        if (isTrigger(KEY_SPACE))param.rotSw = !param.rotSw;
        if (isTrigger(KEY_M))menuSw = !menuSw;
        if (isPress(KEY_UP))hue += 1;
        if (isPress(KEY_DOWN))hue += -1;
        //P�������ꂽ��ő啪������divNum�ɐݒ肷��
        //�ēxP�������ꂽ��Ƃ��Ă��������̒l�ɖ߂�
        if (isTrigger(KEY_P)) {
            if (preDivNum) {
                param.divNum = preDivNum;
                param.w = preW;
                preW = 0;
                preDivNum = 0;
            }
            else {
                preDivNum = param.divNum;
                preW = param.w;
                param.w = 1;
                param.divNum = (int)(width + param.h);
            }
        }
        if (isTrigger(KEY_O)) {
            if (preW) {
                param.w = preW;
                preW = 0;
            }
            else {
                preW = param.w;
                param.w = param.h;
            }
        }
        //�p�^�[���؂�ւ�
        if (isTrigger(KEY_RIGHT) || isTrigger(KEY_LEFT)) {
            if (isTrigger(KEY_RIGHT)) { ++patternNo %= numPattern; }
            else { --patternNo += patternNo <= 0 ? numPattern : 0; }
            param = pattern[patternNo];
        }
        if (isTrigger(KEY_L))param = initPattern[patternNo];
        if (isTrigger(KEY_B))pattern[patternNo] = param;
        //�p�����^�����ɕ`��ɕK�v�Ȓl���v�Z
        float divHue = 360.0f / param.divNum;
        float px = -param.h / 2;
        float space = (width + param.h) / param.divNum;
        float py = height / 2;
        float divAngle = param.coAngle * 360.0f / param.divNum;
        if (param.rotSw) param.rotAngle += param.rotSpeed;
        //rect�`��
        clear(0,0,0);
        for (int i = 0; i <= param.divNum; i++) {
            fill(hue + divHue * i, param.saturation, bright, param.alpha);
            rect(px + space * i, py, param.w, param.h, 
                param.rotAngle + divAngle * i);
        }
        //���j���[�\��
        if (menuSw) {
            fill(0, 0, 255);
            printSize(30);
            print((let)"M:    menu on <-> off");
            print((let)"Q-A:  height=" + param.h);
            print((let)"W-S:  width=" + param.w);
            print((let)"E-D:  divNum=" + param.divNum);
            print((let)"P:    now <-> max divNum");
            print((let)"R-F:  coAngle=" + param.coAngle);
            print((let)"T-G:  alpha=" + param.alpha);
            print((let)"Y-H:  saturation=" + param.saturation);
            print((let)"U-J:  rotSpeed=" + param.rotSpeed);
            print((let)"SPACE:rotSw=" + (param.rotSw ? "on" : "off"));
            print((let)"<-->: Change pattern" );
            print((let)"L:    reset current pattern");
            print((let)"B:    save current pattern");
            //print((let)"rotAngle" + param.rotAngle);
        }
    }
    //���݂̃p�^�[�����Z�[�u
    FILE* ofp = 0;
    fopen_s(&ofp, "assets\\pattern.bin", "wb");
    fwrite(pattern, sizeof(PARAM), numPattern, ofp);
    fclose(ofp);
    ShowCursor(true);
}
