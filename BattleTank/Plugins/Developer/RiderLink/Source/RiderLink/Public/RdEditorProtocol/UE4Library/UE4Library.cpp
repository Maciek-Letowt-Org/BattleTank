//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a RdGen v1.07.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
#include "UE4Library.h"

#include "../UE4Library/StringRange.h"
#include "../UE4Library/PlayState.h"
#include "../UE4Library/LogMessageInfo.h"
#include "../UE4Library/UnrealLogEvent.h"
#include "../UE4Library/UClass.h"
#include "../UE4Library/BlueprintFunction.h"
#include "../UE4Library/ScriptCallStackFrame.h"
#include "../UE4Library/EmptyScriptCallStack.h"
#include "../UE4Library/ScriptCallStack.h"
#include "../UE4Library/UnableToDisplayScriptCallStack.h"
#include "../UE4Library/ScriptMsgException.h"
#include "../UE4Library/ScriptMsgCallStack.h"
#include "../UE4Library/BlueprintHighlighter.h"
#include "../UE4Library/BlueprintReference.h"
#include "../UE4Library/IScriptCallStack_Unknown.h"
#include "../UE4Library/IScriptMsg_Unknown.h"

#include "../UE4Library/UE4Library.h"
#include "../UE4Library/UE4Library.h"
namespace Jetbrains {
    namespace EditorPlugin {
        
        //companion
        
        UE4Library::UE4LibrarySerializersOwner const UE4Library::serializersOwner;
        
        void UE4Library::UE4LibrarySerializersOwner::registerSerializersCore(rd::Serializers const& serializers) const
        {
            serializers.registry<StringRange>();
            serializers.registry<LogMessageInfo>();
            serializers.registry<UnrealLogEvent>();
            serializers.registry<UClass>();
            serializers.registry<BlueprintFunction>();
            serializers.registry<ScriptCallStackFrame>();
            serializers.registry<EmptyScriptCallStack>();
            serializers.registry<ScriptCallStack>();
            serializers.registry<UnableToDisplayScriptCallStack>();
            serializers.registry<ScriptMsgException>();
            serializers.registry<ScriptMsgCallStack>();
            serializers.registry<BlueprintHighlighter>();
            serializers.registry<BlueprintReference>();
            serializers.registry<IScriptCallStack_Unknown>();
            serializers.registry<IScriptMsg_Unknown>();
        }
        
        void UE4Library::connect(rd::Lifetime lifetime, rd::IProtocol const * protocol)
        {
            UE4Library::serializersOwner.registry(protocol->get_serializers());
            
            identify(*(protocol->get_identity()), rd::RdId::Null().mix("UE4Library"));
            bind(lifetime, protocol, "UE4Library");
        }
        
        
        //constants
        
        //initializer
        void UE4Library::initialize()
        {
            serializationHash = -1833244089192435908L;
        }
        
        //primary ctor
        
        //secondary constructor
        
        //default ctors and dtors
        UE4Library::UE4Library()
        {
            initialize();
        }
        
        //reader
        
        //writer
        
        //virtual init
        void UE4Library::init(rd::Lifetime lifetime) const
        {
            rd::RdExtBase::init(lifetime);
        }
        
        //identify
        void UE4Library::identify(const rd::Identities &identities, rd::RdId const &id) const
        {
            rd::RdBindableBase::identify(identities, id);
        }
        
        //getters
        
        //intern
        
        //equals trait
        
        //equality operators
        bool operator==(const UE4Library &lhs, const UE4Library &rhs) {
            return &lhs == &rhs;
        };
        bool operator!=(const UE4Library &lhs, const UE4Library &rhs){
            return !(lhs == rhs);
        }
        
        //hash code trait
        
        //type name trait
        
        //static type name trait
        
        //polymorphic to string
        std::string UE4Library::toString() const
        {
            std::string res = "UE4Library\n";
            return res;
        }
        
        //external to string
        std::string to_string(const UE4Library & value)
        {
            return value.toString();
        }
    };
};
