#include <iostream>
#include "idl.h"
#include "util.h"
#include "schema_generated.h"

using namespace harsh::flat::test;
using namespace std;

int main()
{
    std::cout << "reader!" << std::endl;
    std::string binaryfile;
    bool ok = flatbuffers::LoadFile("texture.bin", false, &binaryfile);


    flatbuffers::FlatBufferBuilder builderOut;
    TextureBuilder* texBuilder = new TextureBuilder(builderOut);
    builderOut.PushBytes(reinterpret_cast<unsigned char*>(const_cast<char *>(binaryfile.c_str())), binaryfile.size());
    std::cout << builderOut.GetSize() << std::endl;

    flatbuffers::Verifier tex_verify(builderOut.GetBufferPointer(), builderOut.GetSize());
    bool verify_flag = VerifyTextureBuffer(tex_verify);


    auto model = GetTexture(builderOut.GetBufferPointer());

    int outNum = model->num_textures();
    const flatbuffers::Vector<flatbuffers::Offset<TextureData>>* outTex = model->textures();
    TextureData* outTexData = (TextureData *)outTex->Get(0);
    int outSize = outTexData->image_size();
    const flatbuffers::Vector<unsigned char>* outData = outTexData->image_data();
    int x = outData->Get(5);
    int len = outData->Length();
    delete texBuilder;
    //builderOut.Finish(model);
    return 0;
}
