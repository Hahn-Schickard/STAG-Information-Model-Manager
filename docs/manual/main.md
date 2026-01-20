# Introduction

STAG Information Model Manager, provides concrete [Information Model](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model) Interface Implementations, as well as concrete [Event_Source](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/cpp-projects/event-model) implementation for [Technology Adapter Interface](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/technology-adapter-interface) and [Data Consumer Adapter Interface](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/data-consumer-adapter-interface) to hook up to.

This module is only meant to be used by the System Runner project and **SHOULD NOT** be used on it's own. For this reason, no usage manual will be provided.

### For maintainers

A high level overview of [Information Model](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model) implementation can be found in [Model Implementation](#model_implementation) chapter. 

An implementation overview of `Technology Adapters` and `Data Consumer Adapters` management as well as communication between them can be found in [Adapter Management](#adapter_management) chapter.
