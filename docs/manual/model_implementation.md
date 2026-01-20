# Model Implementation {#model_implementation}

The diagram bellow showcases a high level overview for the [Information Model](https://git.hahn-schickard.de/hahn-schickard/software-sollutions/application-engineering/internal/opc_ua_dev_group/gateway-project/information-model) implementation. 

@note
In order to keep the `ReadableImpl` as simple as possible, `WritableImpl` does not compose it, but rather defines its own `DataType` and `ReadCallback` fields. Reusing these fields via composition would required adding more logic to `ReadableImpl` that always checks if `ReadCallback` is set.

@note
\n`ObservableImpl` is composed of `ReadableImpl` as originally intended.

## UML Class Diagram

@startuml
hide members
skinparam linetype ortho
skinparam dpi 80

interface MetaInfo as "**<<Information_Model>>**\nMetaInfo"
interface Device as "**<<Information_Model>>**\nDevice" 
class FullMetaInfo as "**<<Information_Model_Manager>>**\nFullMetaInfo"
class DeviceImpl as "**<<Information_Model_Manager>>**\nDeviceImpl"

MetaInfo <|.right. FullMetaInfo
MetaInfo --|> Device
Device <|.left. DeviceImpl

' Space is used to pad the interface so connectors align
interface Element as "**<<Information_Model>>**\n                                                Element                                                "
class ElementImpl as "**<<Information_Model_Manager>>**\nElementImpl"

Element <|.left. ElementImpl

class Spacer
hide Spacer

MetaInfo -[hidden]- Spacer
Device -[hidden]- Spacer
Spacer -[hidden]- Element
MetaInfo --|> Element

interface Observer as "**<<Information_Model>>**\nObserver"
interface Observable as "**<<Information_Model>>**\nObservable"
interface Readable as "**<<Information_Model>>**\nReadable"
interface Writable as "**<<Information_Model>>**\nWritable"
interface Callable as "**<<Information_Model>>**\nCallable"
interface Group as "**<<Information_Model>>**\nGroup"

Device o-- Group

Element --* Group
Element o-- Group
Element *-- Writable
Element *-- Callable
Element *-- Readable
Element *-- Observable

Observable .left.> Observer : creates

class Connection as "**<<Information_Model_Manager>>**\nConnection"
class ObservableImpl as "**<<Information_Model_Manager>>**\nObservableImpl"
class ReadableImpl as "**<<Information_Model_Manager>>**\nReadableImpl"
class WritableImpl as "**<<Information_Model_Manager>>**\nWritableImpl"
class CallableImpl as "**<<Information_Model_Manager>>**\nCallableImpl"
class GroupImpl as "**<<Information_Model_Manager>>**\nGroupImpl"

Group <|.down. GroupImpl
Writable <|.down. WritableImpl
Callable <|.down. CallableImpl
Readable <|.down. ReadableImpl
Observable <|.down. ObservableImpl
ObservableImpl o-right- ReadableImpl
Observer <|.down. Connection

interface ListenerInterface as "**<<Event_Model>>**\nListenerInterface"
class Source as "**<<Event_Model>>**\nSource"
class AsyncListener as "**<<Event_Model>>**\nAsyncListener"

ListenerInterface <|.up. Connection
ListenerInterface .right.> Source : uses
ListenerInterface <|.. AsyncListener
ObservableImpl --o Source 

' Hidden connectors are used to ensure correct left to right order
Observable -[hidden] Readable
Readable -[hidden] Writable
Writable -[hidden] Callable
@enduml
