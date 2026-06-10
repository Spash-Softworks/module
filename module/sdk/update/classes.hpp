#pragma once
#include <cstdint>

//Dump by Vannary 
//Roblox version : version-ad5d3e2906444472
//Roblox hash    : 0.724.0.7240739
//Total classes found: 148
//Total emitted own properties: 483
namespace ClassOffsets {

    namespace Animator {
        inline constexpr uintptr_t RefStepIdForWeight6 = 0x40;
        inline constexpr uintptr_t RefStepIdForWeight7 = 0x40;
        inline constexpr uintptr_t RootMotion = 0x40;
        inline constexpr uintptr_t RootMotionWeight = 0x70;
        inline constexpr uintptr_t PreferLodEnabled = 0x74;
    }

    namespace Atmosphere {
        inline constexpr uintptr_t Color = 0x8;
        inline constexpr uintptr_t Decay = 0x14;
        inline constexpr uintptr_t Density = 0x20;
        inline constexpr uintptr_t Glare = 0x24;
        inline constexpr uintptr_t Haze = 0x28;
        inline constexpr uintptr_t Offset = 0x2c;
    }

    namespace Attachment {
        inline constexpr uintptr_t Axis = 0x10;
        inline constexpr uintptr_t Position = 0x1c;
        inline constexpr uintptr_t SecondaryAxis = 0x28;
        inline constexpr uintptr_t Visible = 0x2c;
    }

    namespace AvatarBodyRules {
        inline constexpr uintptr_t CustomEyebrowId = 0x8;
        inline constexpr uintptr_t CustomEyelashId = 0x10;
        inline constexpr uintptr_t CustomFaceId = 0x18;
        inline constexpr uintptr_t CustomHeadId = 0x20;
        inline constexpr uintptr_t CustomLeftArmId = 0x28;
        inline constexpr uintptr_t CustomLeftLegId = 0x30;
        inline constexpr uintptr_t CustomMoodId = 0x38;
        inline constexpr uintptr_t CustomRightArmId = 0x40;
        inline constexpr uintptr_t CustomRightLegId = 0x48;
        inline constexpr uintptr_t CustomTorsoId = 0x50;
        inline constexpr uintptr_t CustomBodyTypeScale = 0x58;
        inline constexpr uintptr_t CustomHeadScale = 0x60;
        inline constexpr uintptr_t CustomHeight = 0x68;
        inline constexpr uintptr_t CustomHeightScale = 0x70;
        inline constexpr uintptr_t CustomProportionsScale = 0x78;
        inline constexpr uintptr_t CustomEyebrowEnabled = 0x98;
        inline constexpr uintptr_t CustomMoodEnabled = 0x9e;
        inline constexpr uintptr_t KeepPlayerHead = 0xa2;
    }

    namespace BillboardGui {
        inline constexpr uintptr_t Size = 0x28;
        inline constexpr uintptr_t ExtentsOffset = 0x38;
        inline constexpr uintptr_t ExtentsOffsetWorldSpace = 0x44;
        inline constexpr uintptr_t StudsOffset = 0x50;
        inline constexpr uintptr_t StudsOffsetWorldSpace = 0x5c;
        inline constexpr uintptr_t SizeOffset = 0x68;
        inline constexpr uintptr_t Brightness = 0x70;
        inline constexpr uintptr_t CurrentDistance = 0x74;
        inline constexpr uintptr_t DistanceLowerLimit = 0x78;
        inline constexpr uintptr_t DistanceStep = 0x7c;
        inline constexpr uintptr_t DistanceUpperLimit = 0x80;
        inline constexpr uintptr_t LightInfluence = 0x84;
        inline constexpr uintptr_t MaxDistance = 0x88;
        inline constexpr uintptr_t Active = 0x8c;
        inline constexpr uintptr_t AlwaysOnTop = 0x8d;
    }

    namespace BodyColors {
        inline constexpr uintptr_t HeadColor = 0x8;
        inline constexpr uintptr_t HeadColor3 = 0x14;
        inline constexpr uintptr_t LeftArmColor = 0x18;
        inline constexpr uintptr_t LeftArmColor3 = 0x24;
        inline constexpr uintptr_t LeftLegColor = 0x28;
        inline constexpr uintptr_t LeftLegColor3 = 0x34;
        inline constexpr uintptr_t RightArmColor = 0x38;
        inline constexpr uintptr_t RightArmColor3 = 0x44;
        inline constexpr uintptr_t RightLegColor = 0x48;
        inline constexpr uintptr_t RightLegColor3 = 0x54;
        inline constexpr uintptr_t TorsoColor = 0x58;
        inline constexpr uintptr_t TorsoColor3 = 0x64;
    }

    namespace BodyVelocity {
        inline constexpr uintptr_t MaxForce = 0x10;
        inline constexpr uintptr_t Velocity = 0x1c;
    }

    namespace Bone {
        inline constexpr uintptr_t Transform = 0x8;
        inline constexpr uintptr_t TransformedWorldCFrame = 0x8;
    }

    namespace ByteCode {
        inline constexpr uintptr_t Pointer = 0x10;
        inline constexpr uintptr_t Size = 0x20;
    }

    namespace Camera {
        inline constexpr uintptr_t CFrame = 0x18;
        inline constexpr uintptr_t CoordinateFrame = 0x18;
        inline constexpr uintptr_t Focus = 0x48;
        inline constexpr uintptr_t HeadScale = 0x88;
        inline constexpr uintptr_t NearPlaneZ = 0x90;
        inline constexpr uintptr_t MaxAxisFieldOfView = 0x2a8;
        inline constexpr uintptr_t ViewportSize = 0x2a8;
    }

    namespace CanvasGroup {
        inline constexpr uintptr_t ResolutionScale = 0x10;
    }

    namespace Chat {
        inline constexpr uintptr_t BubbleChatEnabled = 0x68;
        inline constexpr uintptr_t IsAutoMigrated = 0x69;
    }

    namespace ChildrenVector {
        inline constexpr uintptr_t Begin = 0x0;
        inline constexpr uintptr_t End = 0x8;
        inline constexpr uintptr_t Stride = 0x10;
    }

    namespace ClassDescriptor {
        inline constexpr uintptr_t ClassName = 0x8;
        inline constexpr uintptr_t Super = 0x10;
    }

    namespace Clouds {
        inline constexpr uintptr_t Color = 0x4;
        inline constexpr uintptr_t Cover = 0xc;
        inline constexpr uintptr_t Density = 0x10;
        inline constexpr uintptr_t Enabled = 0x14;
    }

    namespace Color3Value {
        inline constexpr uintptr_t Value = 0x10;
    }

    namespace DataModel {
        inline constexpr uintptr_t CreatorId = 0x190;
        inline constexpr uintptr_t GameId = 0x198;
        inline constexpr uintptr_t GameLoaded = 0x638;
        inline constexpr uintptr_t JobId = 0x138;
        inline constexpr uintptr_t PlaceId = 0x1a0;
        inline constexpr uintptr_t PlaceVersion = 0x1bc;
        inline constexpr uintptr_t PrimitiveCount = 0x480;
        inline constexpr uintptr_t ScriptContext = 0x440;
        inline constexpr uintptr_t ServerIP = 0x620;
        inline constexpr uintptr_t ToRenderView1 = 0x1d8;
        inline constexpr uintptr_t ToRenderView2 = 0x8;
        inline constexpr uintptr_t ToRenderView3 = 0x28;
        inline constexpr uintptr_t Workspace = 0x178;
    }

    namespace Debris {
        inline constexpr uintptr_t MaxItems = 0x8;
    }

    namespace Decal {
        inline constexpr uintptr_t MetalnessMapContent = 0x8;
        inline constexpr uintptr_t NormalMapContent = 0x38;
        inline constexpr uintptr_t RoughnessMapContent = 0x68;
        inline constexpr uintptr_t ColorMapContent = 0x98;
        inline constexpr uintptr_t TextureContent = 0x98;
        inline constexpr uintptr_t TexturePack = 0xc8;
        inline constexpr uintptr_t Color3 = 0x118;
        inline constexpr uintptr_t UVOffset = 0x11c;
        inline constexpr uintptr_t UVScale = 0x124;
        inline constexpr uintptr_t LocalTransparencyModifier = 0x12c;
        inline constexpr uintptr_t Rotation = 0x130;
        inline constexpr uintptr_t NormalMap = 0x134;
        inline constexpr uintptr_t RoughnessMap = 0x134;
        inline constexpr uintptr_t Shiny = 0x134;
        inline constexpr uintptr_t Specular = 0x138;
        inline constexpr uintptr_t ColorMap = 0x13c;
        inline constexpr uintptr_t Texture = 0x13c;
        inline constexpr uintptr_t Transparency = 0x13c;
        inline constexpr uintptr_t ZIndex = 0x140;
    }

    namespace GamepadService {
        inline constexpr uintptr_t GamepadCursorEnabled = 0x8;
    }

    namespace GuiService {
        inline constexpr uintptr_t IsWindows = 0x28;
        inline constexpr uintptr_t ViewportSizeInMM = 0x38;
        inline constexpr uintptr_t GuiNavigationEnabled = 0x48;
        inline constexpr uintptr_t MenuIsOpen = 0x49;
        inline constexpr uintptr_t TouchControlsEnabled = 0x4a;
        inline constexpr uintptr_t AutoSelectGuiEnabled = 0x419;
        inline constexpr uintptr_t CoreGuiNavigationEnabled = 0x419;
    }

    namespace Highlight {
        inline constexpr uintptr_t FillColor = 0x20;
        inline constexpr uintptr_t OutlineColor = 0x2c;
        inline constexpr uintptr_t FillTransparency = 0x34;
        inline constexpr uintptr_t LineThickness = 0x38;
        inline constexpr uintptr_t OutlineTransparency = 0x3c;
        inline constexpr uintptr_t Enabled = 0x44;
    }

    namespace Humanoid {
        inline constexpr uintptr_t DisplayName = 0x18;
        inline constexpr uintptr_t InternalDisplayName = 0x38;
        inline constexpr uintptr_t CameraOffset = 0x78;
        inline constexpr uintptr_t InternalBodyScale = 0x8c;
        inline constexpr uintptr_t TargetPoint = 0x9c;
        inline constexpr uintptr_t WalkDirection = 0xb0;
        inline constexpr uintptr_t WalkToPoint = 0xb4;
        inline constexpr uintptr_t Health = 0xcc;
        inline constexpr uintptr_t Health_XML = 0xcc;
        inline constexpr uintptr_t HealthDisplayDistance = 0xd0;
        inline constexpr uintptr_t HipHeight = 0xd8;
        inline constexpr uintptr_t InternalHeadScale = 0xdc;
        inline constexpr uintptr_t InternalOriginalHipHeight = 0xe0;
        inline constexpr uintptr_t JumpHeight = 0xe4;
        inline constexpr uintptr_t JumpPower = 0xe8;
        inline constexpr uintptr_t MaxHealth = 0xec;
        inline constexpr uintptr_t MaxSlopeAngle = 0xf0;
        inline constexpr uintptr_t NameDisplayDistance = 0xf4;
        inline constexpr uintptr_t NoFloorTimerState = 0x100;
        inline constexpr uintptr_t TimerState = 0x10c;
        inline constexpr uintptr_t WalkAngleError = 0x110;
        inline constexpr uintptr_t WalkSpeed = 0x114;
        inline constexpr uintptr_t AutoJumpEnabled = 0x118;
        inline constexpr uintptr_t AutoRotate = 0x119;
        inline constexpr uintptr_t AutomaticScalingEnabled = 0x11a;
        inline constexpr uintptr_t BreakJointsOnDeath = 0x11b;
        inline constexpr uintptr_t EvaluateStateMachine = 0x11c;
        inline constexpr uintptr_t FinishedState = 0x11d;
        inline constexpr uintptr_t Jump = 0x11e;
        inline constexpr uintptr_t JumpReplicate = 0x11e;
        inline constexpr uintptr_t OverrideDefaultCollisions = 0x11f;
        inline constexpr uintptr_t PlatformStand = 0x120;
        inline constexpr uintptr_t RequiresNeck = 0x121;
        inline constexpr uintptr_t Sit = 0x122;
        inline constexpr uintptr_t Strafe = 0x123;
        inline constexpr uintptr_t UseJumpPower = 0x124;
        inline constexpr uintptr_t CameraMinDistance = 0x248;
        inline constexpr uintptr_t CameraMaxDistance = 0x24c;
    }

    namespace ImageButton {
        inline constexpr uintptr_t ContentImageSize = 0xc4;
        inline constexpr uintptr_t ImageRectOffset = 0xcc;
        inline constexpr uintptr_t ImageRectSize = 0xd4;
        inline constexpr uintptr_t ImageTransparency = 0xdc;
        inline constexpr uintptr_t SliceScale = 0xe8;
    }

    namespace ImageLabel {
        inline constexpr uintptr_t SliceCenter = 0x38;
        inline constexpr uintptr_t ImageColor3 = 0x58;
        inline constexpr uintptr_t ImageRectOffset = 0x6c;
        inline constexpr uintptr_t ImageRectSize = 0x74;
        inline constexpr uintptr_t ImageTransparency = 0x7c;
        inline constexpr uintptr_t SliceScale = 0x88;
    }

    namespace Instance {
        inline constexpr uintptr_t ChildrenEnd = 0x8;
        inline constexpr uintptr_t UniqueId = 0x8;
        inline constexpr uintptr_t ChildrenStride = 0x10;
        inline constexpr uintptr_t ClassDescriptor = 0x18;
        inline constexpr uintptr_t IsInSandbox = 0x48;
        inline constexpr uintptr_t Name = 0x48;
        inline constexpr uintptr_t Archivable = 0x5c;
        inline constexpr uintptr_t HistoryId = 0x5c;
        inline constexpr uintptr_t Capabilities = 0x5d;
        inline constexpr uintptr_t DefinesCapabilities = 0x5d;
        inline constexpr uintptr_t Sandboxed = 0x5d;
        inline constexpr uintptr_t Children = 0x78;
        inline constexpr uintptr_t ChildrenStart = 0x78;
    }

    namespace Lighting {
        inline constexpr uintptr_t Ambient = 0x10;
        inline constexpr uintptr_t ColorShift_Bottom = 0x1c;
        inline constexpr uintptr_t ColorShift_Top = 0x28;
        inline constexpr uintptr_t FogColor = 0x34;
        inline constexpr uintptr_t OutdoorAmbient = 0x40;
        inline constexpr uintptr_t ShadowColor = 0x4c;
        inline constexpr uintptr_t Brightness = 0x50;
        inline constexpr uintptr_t EnvironmentDiffuseScale = 0x54;
        inline constexpr uintptr_t EnvironmentSpecularScale = 0x58;
        inline constexpr uintptr_t ExposureCompensation = 0x5c;
        inline constexpr uintptr_t FogEnd = 0x64;
        inline constexpr uintptr_t FogStart = 0x68;
        inline constexpr uintptr_t ShadowSoftness = 0x70;
        inline constexpr uintptr_t GlobalShadows = 0x78;
        inline constexpr uintptr_t Outlines = 0x79;
        inline constexpr uintptr_t PrioritizeLightingQuality = 0x7a;
        inline constexpr uintptr_t ClockTime = 0xc0;
        inline constexpr uintptr_t GeographicLatitude = 0xc0;
    }

    namespace LinearVelocity {
        inline constexpr uintptr_t ReactionForceEnabled = 0xc;
    }

    namespace LocalScript {
        inline constexpr uintptr_t ByteCode = 0x1a8;
    }

    namespace MaterialService {
        inline constexpr uintptr_t Use2022Materials = 0x10;
        inline constexpr uintptr_t Use2022MaterialsXml = 0x10;
    }

    namespace MaterialVariant {
        inline constexpr uintptr_t ColorMapContent = 0x8;
        inline constexpr uintptr_t EmissiveMaskContent = 0x38;
        inline constexpr uintptr_t MetalnessMapContent = 0x68;
        inline constexpr uintptr_t NormalMapContent = 0x98;
        inline constexpr uintptr_t RoughnessMapContent = 0xc8;
        inline constexpr uintptr_t TexturePack = 0x198;
        inline constexpr uintptr_t EmissiveTint = 0x1c8;
        inline constexpr uintptr_t AvgMetalness = 0x1d0;
        inline constexpr uintptr_t AvgRoughness = 0x1d4;
        inline constexpr uintptr_t EmissiveStrength = 0x1dc;
        inline constexpr uintptr_t RoughnessMap = 0x1e4;
        inline constexpr uintptr_t StudsPerTile = 0x1e4;
    }

    namespace MeshPart {
        inline constexpr uintptr_t MeshContent = 0x48;
        inline constexpr uintptr_t TextureContent = 0x78;
        inline constexpr uintptr_t VertexCount = 0xc0;
        inline constexpr uintptr_t DoubleSided = 0xc5;
        inline constexpr uintptr_t HasSkinnedMesh = 0xc6;
    }

    namespace Model {
        inline constexpr uintptr_t ModelMeshData = 0x28;
        inline constexpr uintptr_t SlimHash = 0x30;
        inline constexpr uintptr_t WorldPivotData = 0x38;
        inline constexpr uintptr_t ModelMeshCFrame = 0x40;
        inline constexpr uintptr_t ModelMeshSize = 0x70;
        inline constexpr uintptr_t Scale = 0x84;
        inline constexpr uintptr_t ScaleFactor = 0x84;
    }

    namespace ModuleScript {
        inline constexpr uintptr_t UnrestrictedRequireAllowed = 0x8;
        inline constexpr uintptr_t Confidential = 0x70;
        inline constexpr uintptr_t ByteCode = 0x150;
    }

    namespace Motor6D {
        inline constexpr uintptr_t Transform = 0x8;
    }

    namespace Packages {
        inline constexpr uintptr_t SkippedInstancesCount = 0x4;
        inline constexpr uintptr_t IsDehydrated = 0x8;
        inline constexpr uintptr_t ShellPackagesCount = 0x58;
    }

    namespace ParticleEmitter {
        inline constexpr uintptr_t Size = 0x8;
        inline constexpr uintptr_t Squash = 0x48;
        inline constexpr uintptr_t Transparency = 0x88;
        inline constexpr uintptr_t Color = 0xc8;
        inline constexpr uintptr_t Texture = 0x100;
        inline constexpr uintptr_t Acceleration = 0x128;
        inline constexpr uintptr_t FlipbookFramerate = 0x134;
        inline constexpr uintptr_t Lifetime = 0x13c;
        inline constexpr uintptr_t RotSpeed = 0x144;
        inline constexpr uintptr_t Rotation = 0x14c;
        inline constexpr uintptr_t Speed = 0x154;
        inline constexpr uintptr_t SpreadAngle = 0x15c;
        inline constexpr uintptr_t VelocitySpread = 0x15c;
        inline constexpr uintptr_t Brightness = 0x164;
        inline constexpr uintptr_t Drag = 0x168;
        inline constexpr uintptr_t FlipbookSizeX = 0x178;
        inline constexpr uintptr_t FlipbookSizeY = 0x17c;
        inline constexpr uintptr_t LightEmission = 0x180;
        inline constexpr uintptr_t LightInfluence = 0x184;
        inline constexpr uintptr_t LocalTransparencyModifier = 0x188;
        inline constexpr uintptr_t Rate = 0x190;
        inline constexpr uintptr_t ShapePartial = 0x19c;
        inline constexpr uintptr_t TimeScale = 0x1a4;
        inline constexpr uintptr_t VelocityInheritance = 0x1a8;
        inline constexpr uintptr_t ZOffset = 0x1ac;
        inline constexpr uintptr_t Enabled = 0x1b0;
        inline constexpr uintptr_t FlipbookBlendFrames = 0x1b1;
        inline constexpr uintptr_t FlipbookStartRandom = 0x1b2;
        inline constexpr uintptr_t LockedToPart = 0x1b3;
        inline constexpr uintptr_t WindAffectsDrag = 0x1b4;
    }

    namespace Player {
        inline constexpr uintptr_t ChatAvailabilityStatus = 0x38;
        inline constexpr uintptr_t OsPlatform = 0x50;
        inline constexpr uintptr_t DisplayName = 0x78;
        inline constexpr uintptr_t RawJoinData = 0xe8;
        inline constexpr uintptr_t CharacterAppearanceId = 0x210;
        inline constexpr uintptr_t FollowUserId = 0x218;
        inline constexpr uintptr_t FollowUserIdReplicated = 0x218;
        inline constexpr uintptr_t Guest = 0x220;
        inline constexpr uintptr_t CloudEditCameraCoordinateFrame = 0x228;
        inline constexpr uintptr_t ChararacterRegionId = 0x260;
        inline constexpr uintptr_t CameraMaxZoomDistance = 0x268;
        inline constexpr uintptr_t CameraMinZoomDistance = 0x26c;
        inline constexpr uintptr_t HealthDisplayDistance = 0x290;
        inline constexpr uintptr_t InputLatency = 0x294;
        inline constexpr uintptr_t LocaleId = 0x298;
        inline constexpr uintptr_t MaximumSimulationRadius = 0x298;
        inline constexpr uintptr_t NameDisplayDistance = 0x2a0;
        inline constexpr uintptr_t CountryRegionCodeReplicate = 0x2a4;
        inline constexpr uintptr_t SimulationRadius = 0x2a4;
        inline constexpr uintptr_t StepIdOffset = 0x2a8;
        inline constexpr uintptr_t AppearanceDidLoad = 0x2b4;
        inline constexpr uintptr_t AutoJumpEnabled = 0x2b5;
        inline constexpr uintptr_t CanLoadCharacterAppearance = 0x2b7;
        inline constexpr uintptr_t CloudEditPlayerActive = 0x2b8;
        inline constexpr uintptr_t DataComplexity = 0x2b9;
        inline constexpr uintptr_t DataReady = 0x2b9;
        inline constexpr uintptr_t DevEnableMouseLock = 0x2ba;
        inline constexpr uintptr_t HasVerifiedBadge = 0x2bd;
        inline constexpr uintptr_t InternalCharacterAppearanceLoaded = 0x2be;
        inline constexpr uintptr_t NeedRegionalFallback = 0x2bf;
        inline constexpr uintptr_t SuperSafeChatReplicate = 0x2c1;
        inline constexpr uintptr_t Teleported = 0x2c1;
        inline constexpr uintptr_t TeleportedIn = 0x2c2;
        inline constexpr uintptr_t UnfilteredChat = 0x2c4;
        inline constexpr uintptr_t UserId = 0x2c4;
        inline constexpr uintptr_t VREnabled = 0x2c4;
    }

    namespace Players {
        inline constexpr uintptr_t ServerLogPrefix = 0x48;
        inline constexpr uintptr_t MaxPlayers = 0x70;
        inline constexpr uintptr_t MaxPlayersInternal = 0x70;
        inline constexpr uintptr_t PreferredPlayers = 0x74;
        inline constexpr uintptr_t PreferredPlayersInternal = 0x74;
        inline constexpr uintptr_t RespawnTime = 0x78;
        inline constexpr uintptr_t BanningEnabled = 0x7c;
        inline constexpr uintptr_t CharacterAutoLoads = 0x7d;
        inline constexpr uintptr_t UseStrafingAnimations = 0x7e;
        inline constexpr uintptr_t NumPlayers = 0x160;
        inline constexpr uintptr_t BubbleChat = 0x23c;
        inline constexpr uintptr_t ClassicChat = 0x23c;
    }

    namespace ScreenGui {
        inline constexpr uintptr_t ClipToDeviceSafeArea = 0x10;
        inline constexpr uintptr_t OnTopOfCoreBlur = 0x11;
    }

    namespace ScreenshotHud {
        inline constexpr uintptr_t CameraButtonPosition = 0x28;
        inline constexpr uintptr_t UsernameOverlayEnabled = 0x50;
        inline constexpr uintptr_t Visible = 0x51;
    }

    namespace Script {
        inline constexpr uintptr_t ByteCode = 0x1a8;
    }

    namespace ScrollingFrame {
        inline constexpr uintptr_t ScrollRate = 0xfc;
        inline constexpr uintptr_t SmoothScroll = 0x10d;
    }

    namespace Selection {
        inline constexpr uintptr_t ShowActiveInstanceHighlight = 0xc;
    }

    namespace ShirtGraphic {
        inline constexpr uintptr_t Graphic = 0x8;
        inline constexpr uintptr_t Color3 = 0x30;
    }

    namespace Sky {
        inline constexpr uintptr_t SkyboxOrientation = 0x190;
        inline constexpr uintptr_t MoonAngularSize = 0x194;
        inline constexpr uintptr_t StarCount = 0x198;
        inline constexpr uintptr_t SunAngularSize = 0x19c;
        inline constexpr uintptr_t CelestialBodiesShown = 0x1a0;
    }

    namespace Sound {
        inline constexpr uintptr_t IsLoaded = 0x48;
        inline constexpr uintptr_t IsSpatial = 0x48;
        inline constexpr uintptr_t LoopRegion = 0x48;
        inline constexpr uintptr_t Pitch = 0x6c;
        inline constexpr uintptr_t MaxDistance = 0x70;
        inline constexpr uintptr_t RollOffMaxDistance = 0x70;
        inline constexpr uintptr_t EmitterSize = 0x74;
        inline constexpr uintptr_t MinDistance = 0x74;
        inline constexpr uintptr_t RollOffMinDistance = 0x74;
        inline constexpr uintptr_t Volume = 0x80;
        inline constexpr uintptr_t AcousticSimulationEnabled = 0x8c;
        inline constexpr uintptr_t Looped = 0x8d;
        inline constexpr uintptr_t IsPlaying = 0x90;
    }

    namespace SoundGroup {
        inline constexpr uintptr_t Volume = 0x8;
    }

    namespace SoundService {
        inline constexpr uintptr_t AcousticSimulationEnabled = 0x54;
        inline constexpr uintptr_t IsNewExpForAudioApiByDefault = 0x55;
        inline constexpr uintptr_t RespectFilteringEnabled = 0x56;
    }

    namespace SpawnLocation {
        inline constexpr uintptr_t Duration = 0x8;
        inline constexpr uintptr_t TeamColor = 0xc;
        inline constexpr uintptr_t AllowTeamChangeOnTouch = 0x10;
        inline constexpr uintptr_t Enabled = 0x11;
        inline constexpr uintptr_t Neutral = 0x12;
    }

    namespace StarterGui {
        inline constexpr uintptr_t ProcessUserInput = 0x38;
        inline constexpr uintptr_t ShowDevelopmentGui = 0x3a;
    }

    namespace StarterPlayer {
        inline constexpr uintptr_t CameraMaxZoomDistance = 0xc;
        inline constexpr uintptr_t CameraMinZoomDistance = 0x10;
        inline constexpr uintptr_t CharacterJumpHeight = 0x18;
        inline constexpr uintptr_t CharacterJumpPower = 0x1c;
        inline constexpr uintptr_t CharacterMaxSlopeAngle = 0x20;
        inline constexpr uintptr_t CharacterWalkSpeed = 0x24;
        inline constexpr uintptr_t NameDisplayDistance = 0x54;
        inline constexpr uintptr_t AllowCustomAnimations = 0x58;
        inline constexpr uintptr_t AutoJumpEnabled = 0x59;
        inline constexpr uintptr_t CharacterBreakJointsOnDeath = 0x5a;
        inline constexpr uintptr_t ClassicDeath = 0x5c;
        inline constexpr uintptr_t EnableMouseLockOption = 0x5e;
        inline constexpr uintptr_t UserEmotesEnabled = 0x60;
    }

    namespace StringValue {
        inline constexpr uintptr_t Value = 0x18;
    }

    namespace StudioData {
        inline constexpr uintptr_t EnableScriptCollabByDefaultOnLoad = 0x8;
    }

    namespace SunRaysEffect {
        inline constexpr uintptr_t Intensity = 0x4;
        inline constexpr uintptr_t Spread = 0x4;
    }

    namespace SurfaceGui {
        inline constexpr uintptr_t HorizontalCurvature = 0x8;
        inline constexpr uintptr_t MaxDistance = 0xc;
    }

    namespace TeleportService {
        inline constexpr uintptr_t CustomizedTeleportUI = 0x8;
    }

    namespace Terrain {
        inline constexpr uintptr_t ValidationAssetContentMap = 0x8;
        inline constexpr uintptr_t WaterColor = 0x10;
        inline constexpr uintptr_t GrassLength = 0x18;
        inline constexpr uintptr_t WaterReflectance = 0x20;
        inline constexpr uintptr_t WaterTransparency = 0x24;
        inline constexpr uintptr_t IsSmooth = 0x28;
        inline constexpr uintptr_t WaterWaveSize = 0x28;
        inline constexpr uintptr_t WaterWaveSpeed = 0x2c;
        inline constexpr uintptr_t Decoration = 0x30;
        inline constexpr uintptr_t SmoothVoxelsUpgraded = 0x31;
    }

    namespace TestService {
        inline constexpr uintptr_t Description = 0x10;
        inline constexpr uintptr_t SimulateSecondsLag = 0x20;
        inline constexpr uintptr_t Timeout = 0x28;
        inline constexpr uintptr_t ErrorCount = 0x30;
        inline constexpr uintptr_t NumberOfPlayers = 0x34;
        inline constexpr uintptr_t TestCount = 0x38;
        inline constexpr uintptr_t WarnCount = 0x3c;
        inline constexpr uintptr_t AutoRuns = 0x40;
        inline constexpr uintptr_t ExecuteWithStudioRun = 0x41;
        inline constexpr uintptr_t IsPhysicsEnvironmentalThrottled = 0x42;
        inline constexpr uintptr_t IsSleepAllowed = 0x43;
        inline constexpr uintptr_t Is30FpsThrottleEnabled = 0x44;
        inline constexpr uintptr_t ThrottlePhysicsToRealtime = 0x44;
    }

    namespace TextBox {
        inline constexpr uintptr_t ShowNativeInput = 0x1;
        inline constexpr uintptr_t ContentText = 0x8;
        inline constexpr uintptr_t LocalizationMatchIdentifier = 0x28;
        inline constexpr uintptr_t LocalizationMatchedSourceText = 0x48;
        inline constexpr uintptr_t LocalizedPlaceholderText = 0x68;
        inline constexpr uintptr_t LineHeight = 0x108;
        inline constexpr uintptr_t Confidential = 0x139;
        inline constexpr uintptr_t ManualFocusRelease = 0x13a;
        inline constexpr uintptr_t ShouldEmitReturnEvents = 0x13e;
        inline constexpr uintptr_t ShouldEmitTabEvents = 0x13f;
        inline constexpr uintptr_t ShouldEmitUpAndDownArrowEvents = 0x140;
        inline constexpr uintptr_t TextFits = 0x143;
    }

    namespace TextButton {
        inline constexpr uintptr_t ContentText = 0x8;
        inline constexpr uintptr_t LocalizationMatchIdentifier = 0x28;
        inline constexpr uintptr_t LocalizationMatchedSourceText = 0x48;
        inline constexpr uintptr_t LineHeight = 0xd8;
        inline constexpr uintptr_t Confidential = 0xfc;
        inline constexpr uintptr_t TextFits = 0xfe;
    }

    namespace TextChatCommand {
        inline constexpr uintptr_t AutocompleteVisible = 0x40;
        inline constexpr uintptr_t Enabled = 0x41;
        inline constexpr uintptr_t SecondaryAlias = 0x48;
    }

    namespace TextChatService {
        inline constexpr uintptr_t ChatTranslationFTUXShown = 0xff;
        inline constexpr uintptr_t ChatTranslationToggleEnabled = 0xff;
        inline constexpr uintptr_t HasSeenDeprecationDialog = 0x101;
        inline constexpr uintptr_t IsLegacyChatDisabled = 0x102;
    }

    namespace TextLabel {
        inline constexpr uintptr_t ContentText = 0x8;
        inline constexpr uintptr_t LocalizationMatchIdentifier = 0x28;
        inline constexpr uintptr_t LocalizationMatchedSourceText = 0x48;
        inline constexpr uintptr_t LineHeight = 0xd8;
        inline constexpr uintptr_t Confidential = 0xfc;
    }

    namespace TextSource {
        inline constexpr uintptr_t UserId = 0x40;
        inline constexpr uintptr_t UserIdReplicated = 0x40;
        inline constexpr uintptr_t CanSend = 0x48;
        inline constexpr uintptr_t Username = 0x48;
    }

    namespace Tool {
        inline constexpr uintptr_t Grip = 0x28;
        inline constexpr uintptr_t CanBeDropped = 0x58;
        inline constexpr uintptr_t Enabled = 0x59;
        inline constexpr uintptr_t ManualActivationOnly = 0x5a;
    }

    namespace Trail {
        inline constexpr uintptr_t Transparency = 0x8;
        inline constexpr uintptr_t WidthScale = 0x48;
        inline constexpr uintptr_t Color = 0x88;
        inline constexpr uintptr_t Texture = 0xc0;
        inline constexpr uintptr_t Brightness = 0x108;
        inline constexpr uintptr_t Lifetime = 0x10c;
        inline constexpr uintptr_t LightEmission = 0x110;
        inline constexpr uintptr_t LightInfluence = 0x114;
        inline constexpr uintptr_t LocalTransparencyModifier = 0x118;
        inline constexpr uintptr_t MaxLength = 0x11c;
        inline constexpr uintptr_t MinLength = 0x120;
        inline constexpr uintptr_t TextureLength = 0x124;
        inline constexpr uintptr_t Enabled = 0x12c;
        inline constexpr uintptr_t FaceCamera = 0x12d;
    }

    namespace UIPadding {
        inline constexpr uintptr_t PaddingLeft = 0x8;
        inline constexpr uintptr_t PaddingRight = 0x10;
        inline constexpr uintptr_t PaddingTop = 0x18;
    }

    namespace VRService {
        inline constexpr uintptr_t VRDeviceName = 0x8;
        inline constexpr uintptr_t PointerHitCFrame = 0x28;
        inline constexpr uintptr_t QuestDisplayRefreshRate = 0x68;
        inline constexpr uintptr_t AvatarGestures = 0x70;
        inline constexpr uintptr_t DidPointerHit = 0x71;
        inline constexpr uintptr_t FadeOutViewOnCollision = 0x72;
        inline constexpr uintptr_t QuestASWState = 0x73;
        inline constexpr uintptr_t VRDeviceAvailable = 0x74;
        inline constexpr uintptr_t VREnabled = 0x75;
    }

    namespace Workspace {
        inline constexpr uintptr_t TouchesUseCollisionGroups = 0x8;
        inline constexpr uintptr_t WatermarkHash = 0x18;
        inline constexpr uintptr_t FilteringEnabled = 0x28;
        inline constexpr uintptr_t DistributedGameTime = 0x58;
        inline constexpr uintptr_t FallenPartsDestroyHeight = 0x74;
        inline constexpr uintptr_t StreamingMinRadius = 0xd8;
        inline constexpr uintptr_t StreamingTargetRadius = 0xdc;
        inline constexpr uintptr_t ThrottleLevel = 0xe0;
        inline constexpr uintptr_t AllowThirdPartySales = 0xf4;
        inline constexpr uintptr_t ConvexDecompCompressed = 0xf5;
        inline constexpr uintptr_t DataModelPlaceVersion = 0xf6;
        inline constexpr uintptr_t ExplicitAutoJoints = 0xf6;
        inline constexpr uintptr_t FallHeightEnabled = 0xf6;
        inline constexpr uintptr_t InsertPoint = 0xf7;
        inline constexpr uintptr_t StreamingEnabled = 0xf7;
        inline constexpr uintptr_t StreamingEnabledAlias = 0xf7;
        inline constexpr uintptr_t AirDensity = 0x570;
    }

} // namespace ClassOffsets