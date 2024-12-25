#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "global_header.h"
#include "Singleton.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class VerifyGrpcClient : public Singleton<VerifyGrpcClient>{
    friend class Singleton<VerifyGrpcClient>;
public:
    GetVarifyRsp GetVerifyCode(std::string email);

private:
    VerifyGrpcClient();

    std::unique_ptr<VarifyService::Stub> stub_;
};