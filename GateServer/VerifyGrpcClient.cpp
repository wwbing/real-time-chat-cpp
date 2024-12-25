#include "VerifyGrpcClient.h"


VerifyGrpcClient::VerifyGrpcClient() {
    std::shared_ptr<Channel> channel = grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials());
    stub_ = VarifyService::NewStub(channel);
}

GetVarifyRsp VerifyGrpcClient::GetVerifyCode(std::string email) {
    ClientContext context;
    GetVarifyRsp reply;
    GetVarifyReq request;

    request.set_email(email);

    Status status = stub_->GetVarifyCode(&context, request, &reply);
    if (status.ok()) {
        return reply;
    }
    else {
        reply.set_error(ErrorCodes::RPCFailed);
        return reply;
    }
}