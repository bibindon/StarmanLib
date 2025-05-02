#pragma once

#include <vector>
#include <map>

#include "ItemManager.h"

//-------------------------------------------------
// ����`���@�\
//
// �q���������E���Ă����A�C�e�����󂯎���B
// �u�b����������󂯎���v�ł��邱�Ƃɒ��ӁB
// �˗���w���͂ł��Ȃ��B
// �����J���@�ɐG��邽�߁B
// �N���t�g���͎󂯎��Ȃ��B
// 16���ȍ~�ɘb����������󂯎���B
//-------------------------------------------------
namespace NSStarmanLib
{
class Help
{
public:
    static Help* Get();
    static void Destroy();

    void Init(const std::string& filepath, const bool bEnglish);
    void Update();
    void Save(const std::string& filepath);

    // 16���ȍ~�ɘb����������󂯎���B
    // �󂯎����������B
    // �󂯎�炸�ɗ�����16���ɂȂ�����V�����A�C�e���ɂȂ�A�Â����̂͏���
    // 10�܂�
    std::vector<ItemDef> ReceiveItems(const std::string& npcName);

    bool Received(const std::string& npcName);
    bool CanReceive(const std::string& npcName);

private:

    static Help* m_obj;

    std::map<std::string, std::vector<ItemDef>> m_presentMap;

    // 16���𒴂����痂���̓��t��ۑ����A���݂̓��t�Ƃ���
    int m_previousYear = 0;
    int m_previousMonth = 0;
    int m_previousDay = 0;
    int m_previousHour = 0;

    // �A�C�e����n���ς݂�
    std::map<std::string, bool> m_presented;

    std::vector<ItemDef> GetRandomItem(const std::string& npcName);

    bool CrossOver16();

    // �ߋ��ɂ����̂ڂ��Ă���H
    bool BackTime();

    // �E�����Ƃ��\�ȃA�C�e����ID�̃��X�g
    // �E����͂��̂Ȃ��A�C�e�����E���Ȃ��悤�ɂ��邽�߁B
    std::vector<int> m_enableItemIdList;
    bool m_bLoaded = false;
};
}

