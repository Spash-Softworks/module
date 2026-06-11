#pragma once

#include <Windows.h>
#include <memory>

template<typename T>
class VMValue0 {
public:
	operator const T() const { return storage; }
	void operator=(const T& value) { storage = value; }
	const T operator->() const { return operator const T(); }
	T get() { return operator const T(); }
	void set(const T& value) { operator=(value); }

private:
	T storage;
};

template<typename T>
class VMValue1 {
public:
	operator const T() const { return (T)((uintptr_t)storage - (uintptr_t)this); }
	void operator=(const T& value) { storage = (T)((uintptr_t)value + (uintptr_t)this); }
	const T operator->() const { return operator const T(); }
	T get() { return operator const T(); }
	void set(const T& value) { operator=(value); }

private:
	T storage;
};

template<typename T>
class VMValue2 {
public:
	operator const T() const { return (T)((uintptr_t)this - (uintptr_t)storage); }
	void operator=(const T& value) { storage = (T)((uintptr_t)this - (uintptr_t)value); }
	const T operator->() const { return operator const T(); }
	T get() { return operator const T(); }
	void set(const T& value) { operator=(value); }

private:
	T storage;
};

template<typename T>
class VMValue3 {
public:
	operator const T() const { return (T)((uintptr_t)this ^ (uintptr_t)storage); }
	void operator=(const T& value) { storage = (T)((uintptr_t)value ^ (uintptr_t)this); }
	const T operator->() const { return operator const T(); }
	T get() { return operator const T(); }
	void set(const T& value) { operator=(value); }

private:
	T storage;
};

template<typename T>
class VMValue4 {
public:
	operator const T() const { return (T)((uintptr_t)this + (uintptr_t)storage); }
	void operator=(const T& value) { storage = (T)((uintptr_t)value - (uintptr_t)this); }
	const T operator->() const { return operator const T(); }
	T get() { return operator const T(); }
	void set(const T& value) { operator=(value); }

private:
	T storage;
};

#define rebase(address) (address + reinterpret_cast<uintptr_t>(GetModuleHandleA(0)))

namespace RBX::Offsets
{
	namespace VisualEngine
	{
		// use this pattern and u see 
		// mov Pointer, register - the pointer is the address of VisualEnginePointer
		// 48 89 1D ? ? ? ? 8D 48
		const uintptr_t Pointer = rebase(0x77C6670);

		const uintptr_t DeviceD3D11 = 0xA0;
		const uintptr_t SwapChain = 0xC8;

		const uintptr_t FakeDatamodel = 0xA70;
		const uintptr_t Datamodel = 0x1D0; // Fake To Real Datamodel
	}

	namespace TaskScheduler
	{
		// use this string for these offsets
		// "TaskScheduler::Job: "
		// go to first reference and follow tutorials below

		// go to the xref function and go to the first reference
		// sub_xxxxxx(qword_pointer, (__int64)v303); - the qword_pointer, pointer = address below
		const uintptr_t Pointer = rebase(0x7CF5400);

		// this should be above for loop inside the reference of the string
		// 
		// v4 = *(_QWORD*)(a1 + JobStartOffset);
		// for (i = *(_QWORD*)(a1 + JobEndOffset); v4 != i; v4 += 16)
		const uintptr_t JobsStart = 0xC8;

		// v6 = sub_791C70(v18, "TaskScheduler::Job: ");
		// v7 = (_QWORD*)(*(_QWORD*)v4 + JobNameOffset);
		const uintptr_t JobName = 0x18;


		namespace Jobs
		{
			// "Heartbeat" go here and u can find all the offests u need and the place where they set the vtable of a1 (JobBase)
			const uintptr_t HeartbeatToRunService = 0x1A0;
			const uintptr_t HeartbeatVftableSize = 0x48;
			const uintptr_t HeartbeatStepVftableIndex = 0x8;
		}
	}

	namespace GlobalState
	{
		// "Script Start" 1st reference, look for a function with 3 arguements
		//   *(_QWORD *)(ScriptVMState + 256) = "Script Start";
		// this reference uses ScriptVMState which is located in
		// L->userdata->Shared->ScriptVMState
		// so you can just trace it back to L/LuaState and you will
		// eventually see the decryption and the function calling
		// then find the next reference and xref that and u get the address
		const uintptr_t GetGlobalState = rebase(0x1C4BAD0);
	}

	namespace Luau
	{
		const uintptr_t luaH_dummynode = rebase(0x5F518C8);
		const uintptr_t luaO_nilobject = rebase(0x5F52318);

		const uintptr_t luau_execute = rebase(0x43AD490);
		const uintptr_t luaD_throw = rebase(0x4393840);

		const uintptr_t OpCodeLookupTable = rebase(0x646C630);
	}

	namespace TLS
	{
		// "Current Identity is %d" look for first function call in the xref function for this string
		const uintptr_t GetTLSPointer = rebase(0x9060);

		namespace IdentityStructure
		{
			// look for the first instruction that does mov rcx (moving onto 1st arg) and it should be a pointer
			const uintptr_t Pointer = rebase(0x7661528);

			const uintptr_t Capabilities = 0x28;
		}
	}

	namespace Instance
	{
		const uintptr_t Children = 0x78;
		const uintptr_t ChildrenEnd = 0x8;

		const uintptr_t ClassDescriptor = 0x18;
		const uintptr_t ClassName = 0x8;

		const uintptr_t Parent = 0x70;
	}

	namespace Datamodel 
	{
		const uintptr_t PlaceId = 0x198;
		const uintptr_t GameLoadedStatus = 0x5F8;
	}
}

namespace RBX
{
	class class_functions
	{
	private:
		using tGetGlobalState = uintptr_t(__fastcall*)(uintptr_t ScriptContext, uintptr_t* Identity, uintptr_t* Script);

		using tGetTLSPointer = uintptr_t(__fastcall*)(uintptr_t Pointer);

	public:

		tGetGlobalState GetGlobalState = reinterpret_cast<tGetGlobalState>(RBX::Offsets::GlobalState::GetGlobalState);

		tGetTLSPointer GetTLSPointer = reinterpret_cast<tGetTLSPointer>(RBX::Offsets::TLS::GetTLSPointer);
	};

	inline auto Functions = std::make_unique<class_functions>();
}

#define CLOSURE_CONT_ENC VMValue3
#define CLOSURE_DEBUGNAME_ENC VMValue4
#define LSTATE_STACKSIZE_ENC VMValue4
#define PROTO_ABSLINEINFO_ENC VMValue1
#define PROTO_DEBUGINSN_ENC VMValue2
#define PROTO_DEBUGNAME_ENC VMValue1
#define PROTO_LINEINFO_ENC VMValue4
#define PROTO_LOCVARS_ENC VMValue1
#define PROTO_SOURCE_ENC VMValue3
#define PROTO_TYPEINFO_ENC VMValue2
#define PROTO_UPVALUES_ENC VMValue2
#define PROTO_USERDATA_ENC VMValue3
#define TSTRING_HASH_ENC VMValue4
#define UDATA_META_ENC VMValue4