# Make sure you are working on a RHEL system!

# Development stage for development
FROM registry.access.redhat.com/ubi8/ubi:latest AS development

# Upgrade all packages and grab required packages.
RUN dnf --assumeyes upgrade
RUN dnf --assumeyes install clang lldb cmake python39 python39-pip perl
RUN pip3 install conan

WORKDIR /root
CMD [ "/bin/bash" ]

# Production stage for deployment
FROM registry.access.redhat.com/ubi8/ubi:latest AS production
ARG PROJECT_BUILD_DIR

RUN dnf --assumeyes upgrade
RUN mkdir /opt/microservice

COPY ${PROJECT_BUILD_DIR}/build/production/package /opt/microservice
ENTRYPOINT [ "/opt/microservice/bin/BossCppServer" ]
