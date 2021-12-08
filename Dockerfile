# Make sure you are working on a RHEL system!

# Development stage for development
FROM registry.access.redhat.com/ubi8/ubi:latest AS development

# Upgrade all packages and grab required packages.
RUN dnf --assumeyes upgrade
RUN dnf --assumeyes install clang lldb cmake python39 python39-pip perl
RUN pip3 install conan

WORKDIR /root
ENV PATH="/root/.conan/data/protobuf/3.17.1/_/_/package/8b7c9763c797cff35375f939b7f2d125dc808549/bin:\
/root/.conan/data/grpc/1.39.1/LeftRuleMatters/stable/package/48992b9c2c80b89c4d5f3001c126cb945bdd9e72/bin:\
${PATH}"

CMD [ "/bin/bash" ]

# Production stage for deployment
FROM registry.access.redhat.com/ubi8/ubi:latest AS production
ARG PROJECT_BUILD_DIR

RUN dnf --assumeyes upgrade
RUN mkdir /opt/microservice

COPY ${PROJECT_BUILD_DIR}/build/production/package /opt/microservice
ENTRYPOINT [ "/opt/microservice/bin/BossCppServer" ]
