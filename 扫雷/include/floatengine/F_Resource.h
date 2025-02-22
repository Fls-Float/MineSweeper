#ifndef F_RESOURCE_H
#define F_RESOURCE_H

#include <raylib.hpp>
#include <map>
#include <string>
#include <vector>

enum ResourceType {
    ResText,
    ResSound,
    ResMusic,
    ResTexture,
    ResFont,
    ResData
};

class F_Resource {
    const char* _password;
    std::string _zip_path;
    bool has_password;
public:
    // ���캯������������
    F_Resource();
    ~F_Resource();
    //����zip·��
    void SetZipPath(const std::string& path);
    // ѹ��������
    void SetPassword(const char* password);
    //��ʹ������
    void NoPassword();

    //����ѹ����
    inline void Setup(const std::string& path, const char* password="",bool _has_password=0) {
        SetZipPath(path);
        SetPassword(password);
        has_password = _has_password;
    }
    // ������Դ(font���⴦��)
    bool LoadResource(const std::string& path, const std::string& id, ResourceType type);
    //��������
    bool LoadFontResource(const std::string& path, const std::string& id, int font_size, int* codepoints, int codepoints_size);
    //������Դ
    void AddResource(const std::string& id, ResourceType type, void* resource);
    // ��ȡ��Դ
    Texture2D GetTexture(const std::string& id);
    Sound GetSound(const std::string& id);
    Music GetMusic(const std::string& id);
    Font GetFont(const std::string& id);
    std::string GetText(const std::string& id);
    std::vector<unsigned char> GetData(const std::string& id);
    bool HasResource(const std::string& id);
    bool HasResource(const std::string& id,ResourceType type);
    // ��ȡ��Դָ��
    Texture2D* GetTextureP(const std::string& id);
    Sound* GetSoundP(const std::string& id);
    Music* GetMusicP(const std::string& id);
    Font* GetFontP(const std::string& id);
    std::string* GetTextP(const std::string& id);
    
    // ж�ص�����Դ
    void UnloadResource(const std::string& id, ResourceType type);

    // ж��������Դ
    void UnloadAllResources();

private:
    // ��Դ����
    std::map<std::string, Texture2D> textures;
    std::map<std::string, Sound> sounds;
    std::map<std::string, Music> musics;
    std::map<std::string, Font> fonts;
    std::map<std::string, std::string> texts;
    std::map < std::string, std::vector<unsigned char>> datas;
    // ��Դ���ظ�������
    bool LoadTextureFromZlib(const std::string& path, const std::string& id);
    bool LoadSoundFromZlib(const std::string& path, const std::string& id);
    bool LoadMusicFromZlib(const std::string& path, const std::string& id);
    bool LoadFontFromZlib(const std::string& path, const std::string& id, int font_size, int* codepoints, int codepoints_size);
    bool LoadTextFromZlib(const std::string& path, const std::string& id);
	bool LoadDataFromZlib(const std::string& path, const std::string& id);
    // ж����Դ��������
    void UnloadTextureById(const std::string& id);
    void UnloadSoundById(const std::string& id);
    void UnloadMusicById(const std::string& id);
    void UnloadFontById(const std::string& id);
    void UnloadTextById(const std::string& id);
    void UnloadDataById(const std::string& id);
    // ��ѹ����������
    bool DecompressZlib(const std::string& path, std::vector<unsigned char>& out_data);
    bool DecompressZlibWithPassword(const std::string& path, std::vector<unsigned char>& out_data, const char* password);
};

#endif // F_RESOURCE_H
