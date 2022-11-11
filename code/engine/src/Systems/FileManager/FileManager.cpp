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

    std::string FileManager::getAsset(assets::Sounds sound) {
        return {};
    }

    std::string FileManager::getAsset(assets::Materials material) {
        return {};
    }

    std::string FileManager::getAsset(assets::Images image) {
        return {};
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

    const aiScene* FileManager::loadModelFromFile(const fs::path &relativeFilePath) {
        Assimp::Importer importer;
        const aiScene *modelScene = importer.ReadFile(relativeFilePath.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

        if(!modelScene || modelScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !modelScene->mRootNode) {
            throw std::runtime_error("ERROR::ASSIMP::" + std::string(importer.GetErrorString()));
        }
        return modelScene;
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
    }

    FileManager::~FileManager() {
        shaderCache.release();
        modelCache.release();
    }
}

