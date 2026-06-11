#include "TaskScheduler.hpp"

#include "update.hpp"

#include "Execution/Execution.hpp"

uintptr_t RBX::TaskScheduler::GetDatamodel()
{
	uintptr_t VisualEngine = *reinterpret_cast<uintptr_t*>(RBX::Offsets::VisualEngine::Pointer);
	if (!VisualEngine) {
		return 0;
	}

	uintptr_t FakeDatamodel = *reinterpret_cast<uintptr_t*>(VisualEngine + RBX::Offsets::VisualEngine::FakeDatamodel);
	if (!FakeDatamodel) {
		return 0;
	}

	uintptr_t Datamodel = *reinterpret_cast<uintptr_t*>(FakeDatamodel + RBX::Offsets::VisualEngine::Datamodel);
	if (!Datamodel) {
		return 0;
	}

	return Datamodel;
}

uintptr_t RBX::TaskScheduler::GetScriptContext(uintptr_t Datamodel)
{
	if (!Datamodel) {
		return 0;
	}

	uintptr_t DatamodelChildrenPointer = *reinterpret_cast<uintptr_t*>(Datamodel + RBX::Offsets::Instance::Children);
	if (!DatamodelChildrenPointer) {
		return 0;
	}

	uintptr_t ChildrenStart = *reinterpret_cast<uintptr_t*>(DatamodelChildrenPointer);
	if (!ChildrenStart) {
		return 0;
	}

	uintptr_t ChildrenEnd = *reinterpret_cast<uintptr_t*>(DatamodelChildrenPointer + RBX::Offsets::Instance::ChildrenEnd);
	if (!ChildrenEnd) {
		return 0;
	}

	uintptr_t ScriptContext = 0;

	for (uintptr_t ChildPointer = ChildrenStart; ChildPointer < ChildrenEnd; ChildPointer += 0x10)
	{
		if (!ChildPointer) {
			continue;
		}

		uintptr_t Child = *reinterpret_cast<uintptr_t*>(ChildPointer);
		if (!Child) {
			continue;
		}

		uintptr_t ClassDescriptor = *reinterpret_cast<uintptr_t*>(Child + RBX::Offsets::Instance::ClassDescriptor);
		if (!ClassDescriptor) {
			continue;
		}

		const char* ClassName = *reinterpret_cast<const char**>(ClassDescriptor + RBX::Offsets::Instance::ClassName);
		if (!ClassName) {
			continue;
		}

		if (std::string(ClassName) == "ScriptContext") {
			ScriptContext = Child;
			break;
		}
	}

	return ScriptContext;
}

uintptr_t RBX::TaskScheduler::GetPlaceId(uintptr_t Datamodel)
{
	if (!Datamodel) {
		return 0;
	}

	return *reinterpret_cast<uintptr_t*>(Datamodel + RBX::Offsets::Datamodel::PlaceId);
}

int RBX::TaskScheduler::GetGameLoadedStatus(uintptr_t Datamodel)
{
	if (!Datamodel) {
		return 0;
	}

	return *reinterpret_cast<int*>(Datamodel + RBX::Offsets::Datamodel::GameLoadedStatus);
}

uintptr_t RBX::TaskScheduler::GetGlobalState(uintptr_t ScriptContext, uintptr_t* Identity, uintptr_t* Script)
{
	if (!ScriptContext) {
		return 0;
	}

	return RBX::Functions->GetGlobalState(ScriptContext, Identity, Script);
}

uintptr_t RBX::TaskScheduler::GetJobByName(std::string TargetJobName)
{
	uintptr_t TaskScheduler = *reinterpret_cast<uintptr_t*>(RBX::Offsets::TaskScheduler::Pointer);
	if (!TaskScheduler) {
		return 0;
	}

	uintptr_t JobsStart = *reinterpret_cast<uintptr_t*>(TaskScheduler + RBX::Offsets::TaskScheduler::JobsStart);
	if (!JobsStart) {
		return 0;
	}

	uintptr_t JobsEnd = *reinterpret_cast<uintptr_t*>(TaskScheduler + RBX::Offsets::TaskScheduler::JobsStart + sizeof(uintptr_t));
	if (!JobsEnd) {
		return 0;
	}

	uintptr_t JobResult = 0;

	for (uintptr_t JobPointer = JobsStart; JobPointer < JobsEnd; JobPointer += 0x10) 
	{
		if (!JobPointer) {
			continue;
		}

		uintptr_t Job = *reinterpret_cast<uintptr_t*>(JobPointer);
		if (!Job) {
			continue;
		}

		const char* JobName = *reinterpret_cast<const char**>(Job + RBX::Offsets::TaskScheduler::JobName);
		if (!JobName) {
			continue;
		}

		if (std::string(JobName) == TargetJobName) {
			JobResult = Job;
			break;
		}
	}

	return JobResult;
}

uintptr_t RBX::TaskScheduler::GetSpecificJobByName(std::string TargetJobName, uintptr_t Offset, uintptr_t Datamodel)
{
	uintptr_t TaskScheduler = *reinterpret_cast<uintptr_t*>(RBX::Offsets::TaskScheduler::Pointer);
	if (!TaskScheduler) {
		return 0;
	}

	uintptr_t JobsStart = *reinterpret_cast<uintptr_t*>(TaskScheduler + RBX::Offsets::TaskScheduler::JobsStart);
	if (!JobsStart) {
		return 0;
	}

	uintptr_t JobsEnd = *reinterpret_cast<uintptr_t*>(TaskScheduler + RBX::Offsets::TaskScheduler::JobsStart + sizeof(uintptr_t));
	if (!JobsEnd) {
		return 0;
	}

	uintptr_t JobResult = 0;

	for (uintptr_t JobPointer = JobsStart; JobPointer < JobsEnd; JobPointer += 0x10)
	{
		uintptr_t Job = *reinterpret_cast<uintptr_t*>(JobPointer);
		if (!Job) {
			continue;
		}

		std::string JobName = *reinterpret_cast<std::string*>(Job + RBX::Offsets::TaskScheduler::JobName);
		if (JobName.empty()) {
			continue;
		}

		if (JobName == TargetJobName) {
			uintptr_t Instance = *reinterpret_cast<uintptr_t*>(Job + Offset);
			if (!Instance) {
				continue;
			}

			uintptr_t PossibleDatamodel = *reinterpret_cast<uintptr_t*>(Instance + RBX::Offsets::Instance::Parent);
			if (!PossibleDatamodel) {
				continue;
			}

			if (PossibleDatamodel == Datamodel) {
				JobResult = Job;
				break;
			}
		}
	}

	return JobResult;
}

uintptr_t RBX::TaskScheduler::GetCapabilities(int Identity)
{
	uintptr_t result;

	switch (Identity)
	{
	case 1:
	case 4:
		result = 0x2000000000000003LL;
		break;
	case 3:
		result = 0x300000000000000BLL;
		break;
	case 5:
		result = 0x2000000000000001LL;
		break;
	case 6:
		result = 0x700000000000000BLL;
		break;
	case 7:
	case 8:
		result = 0x200000000000003FLL;
		break;
	case 9:
	case 0xD:
		result = 12;
		break;
	case 0xA:
		result = 0x6000000000000003LL;
		break;
	case 0xB:
		result = 0x2000000000000000LL;
		break;
	case 0xC:
		result = 0x1000000000000000LL;
		break;
	default:
		result = 0;
		break;
	}

	return result | 0x3FFFFFFFFFFF00LL;
}

void RBX::TaskScheduler::SetIdentity(lua_State* Thread, int Identity, bool IsInstance)
{
	Thread->userdata->Identity = 8;
	Thread->userdata->Capabilities = GetCapabilities(Identity);

	if (IsInstance) {
		uintptr_t IdentityPointer = *reinterpret_cast<uintptr_t*>(RBX::Offsets::TLS::IdentityStructure::Pointer);
		if (!IdentityPointer) {
			return;
		}

		uintptr_t IdentityStructure = RBX::Functions->GetTLSPointer(IdentityPointer);
		if (!IdentityStructure) {
			return;
		}

		*reinterpret_cast<int32_t*>(IdentityStructure) = Identity;
		*reinterpret_cast<uintptr_t*>(IdentityStructure + RBX::Offsets::TLS::IdentityStructure::Capabilities) = GetCapabilities(Identity);
	}
}

void RBX::TaskScheduler::SendScript(const std::string& Script)
{
	RBX::Execution::ExecuteScript(RBX::ExecutorState, Script);
}