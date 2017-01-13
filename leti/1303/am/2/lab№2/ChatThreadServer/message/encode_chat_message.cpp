
#include <QString>
#include <QDataStream>
#include "encode_chat_message.h"
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
using namespace std;
using namespace google::protobuf::io;

EncodeChatMessage::EncodeChatMessage()
{

}

 EncodedChatMessage EncodeChatMessage::encodeChatMessage(ChatMessage &chatMessage){

    QString chatMessageAsString=chatMessage.SerializeAsString().data();

    quint8 countByte;
    quint32 lenghtChatMessage=chatMessageAsString.length();
    quint8 bufferEncodeLength[4];
    QByteArray baCountByte,baEncodeLength;
    QByteArray baChatMessage;
    QDataStream outBaEncodeLength(&baEncodeLength,QIODevice::WriteOnly);

    ZeroCopyOutputStream* raw_output = new ArrayOutputStream(bufferEncodeLength,sizeof(bufferEncodeLength));
    CodedOutputStream* coded_output = new CodedOutputStream(raw_output);
    coded_output->WriteVarint32(lenghtChatMessage);

    countByte=coded_output->ByteCount();

    baCountByte.append(countByte);
    for(quint8 i=0;i<countByte;i++){
        outBaEncodeLength<<bufferEncodeLength[i];
    }
    baChatMessage.append(chatMessageAsString);

    return EncodedChatMessage(baCountByte,baEncodeLength,baChatMessage);

}
