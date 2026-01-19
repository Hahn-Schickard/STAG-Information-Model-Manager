# Model Implementation {#model_implementation}

The diagram bellow showcases a high level UML class diagram for [Information Model](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model) implementation. 

@note
In order to keep the `ReadableImpl` as simple as possible, `WritableImpl` does not compose it, but rather defines its own `DataType` and `ReadCallback` fields. Reusing these fields via composition would required adding more logic to `ReadableImpl` that always checks if `ReadCallback` is set.

@note
\n`ObservableImpl` is composed of `ReadableImpl` as originally intended.

## UML Class Diagram

@startuml
hide members
skinparam linetype ortho

interface MetaInfo as "**<<Information_Model>>**\nMetaInfo"
interface Device as "**<<Information_Model>>**\nDevice" 
class FullMetaInfo as "**<<Information_Model_Manager>>**\nFullMetaInfo"
class DeviceImpl as "**<<Information_Model_Manager>>**\nDeviceImpl"

MetaInfo <|.right. FullMetaInfo
MetaInfo --|> Device
Device <|.left. DeviceImpl

' Space is used to pad the interface so connectors align 
interface Element as "                        **<<Information_Model>>**                        \n                        Element                        "

class Spacer
hide Spacer

MetaInfo -[hidden]- Spacer
Device -[hidden]- Spacer
Spacer -[hidden]- Element
MetaInfo --|> Element

together {
  interface Group as "**<<Information_Model>>**\nGroup"
  interface Readable as "**<<Information_Model>>**\nReadable"
  interface Writable as "**<<Information_Model>>**\nWritable"
  interface Observable as "**<<Information_Model>>**\nObservable"
  interface Callable as "**<<Information_Model>>**\nCallable"
}

class ElementImpl as "**<<Information_Model_Manager>>**\nElementImpl"
class GroupImpl as "**<<Information_Model_Manager>>**\nGroupImpl"
class ReadableImpl as "**<<Information_Model_Manager>>**\nReadableImpl"
class WritableImpl as "**<<Information_Model_Manager>>**\nWritableImpl"
class ObservableImpl as "**<<Information_Model_Manager>>**\nObservableImpl"
class CallableImpl as "**<<Information_Model_Manager>>**\nCallableImpl"

Element <|.left. ElementImpl
Device o-- Group

Element *-- Readable
Element *-- Writable
Element *-- Observable
Element *-- Callable
Element --* Group
Element o-- Group

Readable <|.down. ReadableImpl
Writable <|.down. WritableImpl
Observable <|.down. ObservableImpl
Callable <|.down. CallableImpl
Group <|.down. GroupImpl
@enduml
