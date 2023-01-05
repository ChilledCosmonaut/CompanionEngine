#include "engine/Systems/FileManager/FileManager.h"

namespace  gl3::engine::filesystem{

    FileManager *FileManager::GetFileManager() {
        if (fileManager == nullptr)
            fileManager = new FileManager();
        return fileManager;
    }

    void FileManager::DestroyFileManager() {
        if(fileManager == nullptr)
            return;
        fileManager->~FileManager();
        fileManager = nullptr;
    }

    std::shared_ptr<Graphics::shader> FileManager::getAsset(assets::Shaders vertexShader, assets::Shaders fragmentShader) {
        if (!shaderCache->Contains(shaderId(vertexShader, fragmentShader))) {
            //Construct item here
            auto shader = shaderCache->AddItem(shaderId(vertexShader, fragmentShader));
            std::string vertexText = readText(assets::AssetTranslator::TranslateShader(vertexShader));
            std::string fragmentText = readText(assets::AssetTranslator::TranslateShader(fragmentShader));
            shader->SetUp(vertexText, fragmentText);
        }
        return shaderCache->Get(shaderId(vertexShader, fragmentShader));
    }

    std::shared_ptr<Graphics::ModelData> FileManager::getAsset(assets::Models model) {
        if (!modelCache->Contains(model)) {
            //Construct item here
            auto modelData = modelCache->AddItem(model);
            ModelLoader::LoadModel(*modelData, assets::AssetTranslator::TranslateModel(model));
        }
        return modelCache->Get(model);
    }

    std::shared_ptr<SoLoud::Wav> FileManager::getAsset(assets::Sounds sound) {
        if (!soundCache->Contains(sound)) {
            //Construct item here
            auto soundData = soundCache->AddItem(sound);
            soundData->load(assets::AssetTranslator::TranslateSound(sound).string().c_str());
        }
        return soundCache->Get(sound);
    }

    std::string FileManager::getAsset(assets::Materials material) {
        return {};
    }

    std::shared_ptr<Graphics::Texture> FileManager::getAsset(assets::Images image) {
        if (!imageCache->Contains(image)) {
            //Construct item here
            auto textureData = imageCache->AddItem(image);
            textureData->name = image;
            TextureLoader::TextureFromFile(*textureData, assets::AssetTranslator::TranslateImage(image));
        }
        return imageCache->Get(image);
    }

    std::shared_ptr<std::map<GLchar, Character>> FileManager::getFont(assets::Fonts font, int fontSize){
        if (!fontCache->Contains(fontId(font, fontSize))) {
            //Construct item here
            auto characterSet = fontCache->AddItem(fontId(font, fontSize));
            FontLoader::LoadFont(characterSet, assets::AssetTranslator::TranslateFonts(font), fontSize);
        }
        return fontCache->Get(fontId(font, fontSize));
    }

    void FileManager::writeFileToTemp(const char *stringToSave, const std::filesystem::path &fileName) {
        fs::path tempFilePath = resolveForSubdirectory(fileName, std::filesystem::temp_directory_path());
        saveTextAt(stringToSave, tempFilePath);
    }

    void FileManager::saveFileAt(const char *stringToSave, const std::filesystem::path &relativeFilePath) {
        fs::path tempFilePath = resolveForSubdirectory(relativeFilePath, "../..");
        saveTextAt(stringToSave, tempFilePath);
    }

    std::string FileManager::readText(const std::filesystem::path &fileName) {
        std::ifstream sourceFile(fileName);
        std::stringstream buffer;
        buffer << sourceFile.rdbuf();
        sourceFile.close();
        return buffer.str();
    }

    void FileManager::saveTextAt(const char *stringToSave, const std::filesystem::path &fileName) {
        std::ofstream sourceFile(fileName);
        sourceFile << sourceFile.rdbuf();
        sourceFile.close();
    }

    texture FileManager::loadTextureFromFile(const fs::path &relativeFilePath) {
        texture textureFile{};
        std::string stringFilePath = resolveForSubdirectory(relativeFilePath, "../../assets/textures").string();
        const char* filePath = stringFilePath.c_str();
        textureFile.content = stbi_load(filePath, &textureFile.width, &textureFile.height, &textureFile.colChannel, 0);
        return textureFile;
    }

    FileManager::FileManager() {
        shaderCache = std::make_unique<Cache<shaderId,  Graphics::shader>>(30);
        modelCache = std::make_unique<Cache<assets::Models, Graphics::ModelData>>(30);
        soundCache = std::make_unique<Cache<assets::Sounds, SoLoud::Wav>>(30);
        imageCache = std::make_unique<Cache<assets::Images, Graphics::Texture>>(30);
        fontCache = std::make_unique<Cache<fontId, std::map<GLchar, Character>>>(30);
    }

    FileManager::~FileManager() {
        shaderCache.release();
        modelCache.release();
        soundCache.release();
        imageCache.release();
        fontCache.release();
    }
}

