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
    // 构造函数和析构函数
    F_Resource();
    ~F_Resource();
    //设置zip路径
    void SetZipPath(const std::string& path);
    // 压缩包密码
    void SetPassword(const char* password);
    //不使用密码
    void NoPassword();

    //设置压缩包
    inline void Setup(const std::string& path, const char* password="",bool _has_password=0) {
        SetZipPath(path);
        SetPassword(password);
        has_password = _has_password;
    }
    // 加载资源(font额外处理)
    bool LoadResource(const std::string& path, const std::string& id, ResourceType type);
    //加载字体
    bool LoadFontResource(const std::string& path, const std::string& id, int font_size, int* codepoints, int codepoints_size);
    //加入资源
    void AddResource(const std::string& id, ResourceType type, void* resource);
    // 获取资源
    Texture2D GetTexture(const std::string& id);
    Sound GetSound(const std::string& id);
    Music GetMusic(const std::string& id);
    Font GetFont(const std::string& id);
    std::string GetText(const std::string& id);
    std::vector<unsigned char> GetData(const std::string& id);
    bool HasResource(const std::string& id);
    bool HasResource(const std::string& id,ResourceType type);
    // 获取资源指针
    Texture2D* GetTextureP(const std::string& id);
    Sound* GetSoundP(const std::string& id);
    Music* GetMusicP(const std::string& id);
    Font* GetFontP(const std::string& id);
    std::string* GetTextP(const std::string& id);
    
    // 卸载单个资源
    void UnloadResource(const std::string& id, ResourceType type);

    // 卸载所有资源
    void UnloadAllResources();

private:
    // 资源缓存
    std::map<std::string, Texture2D> textures;
    std::map<std::string, Sound> sounds;
    std::map<std::string, Music> musics;
    std::map<std::string, Font> fonts;
    std::map<std::string, std::string> texts;
    std::map < std::string, std::vector<unsigned char>> datas;
    // 资源加载辅助函数
    bool LoadTextureFromZlib(const std::string& path, const std::string& id);
    bool LoadSoundFromZlib(const std::string& path, const std::string& id);
    bool LoadMusicFromZlib(const std::string& path, const std::string& id);
    bool LoadFontFromZlib(const std::string& path, const std::string& id, int font_size, int* codepoints, int codepoints_size);
    bool LoadTextFromZlib(const std::string& path, const std::string& id);
	bool LoadDataFromZlib(const std::string& path, const std::string& id);
    // 卸载资源辅助函数
    void UnloadTextureById(const std::string& id);
    void UnloadSoundById(const std::string& id);
    void UnloadMusicById(const std::string& id);
    void UnloadFontById(const std::string& id);
    void UnloadTextById(const std::string& id);
    void UnloadDataById(const std::string& id);
    // 解压缩辅助函数
    bool DecompressZlib(const std::string& path, std::vector<unsigned char>& out_data);
    bool DecompressZlibWithPassword(const std::string& path, std::vector<unsigned char>& out_data, const char* password);
};

#endif // F_RESOURCE_H
