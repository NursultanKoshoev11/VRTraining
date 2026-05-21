# VRTraining — Production Project Documentation

## 1. Project Summary

**VRTraining** is the production Unreal Engine VR client for **BuildSafe VR**, a B2B construction safety training platform. The application is designed for real training operations, not for a prototype-only or experimental demo. The goal is to deliver a stable, measurable, secure, and repeatable VR training experience that can be used by construction companies, safety training centers, vocational schools, community colleges, and apprenticeship programs.

The VR client runs the immersive training experience. It places a trainee inside a realistic construction environment, gives the trainee safety tasks, records important training actions, calculates local results, stores data safely if the device is offline, and synchronizes the completed training session with the backend server.

This client must be developed with production expectations from the beginning:

- stable VR performance;
- reliable session tracking;
- secure server communication;
- offline-safe data storage;
- clear user experience;
- multilingual training content;
- versioned training modules;
- audit-friendly training results;
- maintainable Unreal architecture;
- release-ready Quest builds.

The application is not positioned as an official certification product. It is positioned as **supplemental VR safety training** and **OSHA-aligned hazard recognition practice**. The product supports training and documentation, but it must not claim to replace official employer-required training, OSHA-authorized courses, or legal safety obligations.

---

## 2. Production Product Vision

The production vision is to build a VR safety training client that companies can use repeatedly with real workers or students. The product must help trainees practice safety decisions before they face similar risks on a real jobsite.

A production training session must answer three questions:

1. Did the trainee understand the task?
2. Did the trainee recognize the hazards?
3. Can the safety manager review clear evidence of the trainee’s performance?

The VR client must create the training experience, but the result must be measurable. Every completed session must produce structured data that can be sent to the backend and displayed in reports.

The long-term product direction is a modular VR training platform where each module is versioned, measurable, localizable, and connected to the server-side reporting system.

---

## 3. Production Positioning Rules

The application can be described as:

- supplemental construction safety training;
- VR hazard recognition training;
- OSHA-aligned safety awareness practice;
- Focus Four hazard awareness training support;
- supervisor-ready VR training data collection;
- repeatable VR safety training scenario system.

The application must not be described as:

- official OSHA certification;
- OSHA-approved certification;
- replacement for OSHA 10 or OSHA 30;
- replacement for employer-specific training;
- legal proof of full compliance by itself;
- guarantee that accidents will not happen.

This wording matters because the product will be sold to real organizations. Incorrect safety or certification claims can create legal and business risk.

---

## 4. Role of the VR Client

This repository contains only the Unreal Engine VR client. The VR client is responsible for the interactive training experience and the client-side session lifecycle.

The VR client must handle:

1. VR device startup and runtime configuration.
2. User login, PIN entry, or QR-based session access.
3. Language selection.
4. Training module selection.
5. Construction site environment rendering.
6. VR movement and interaction.
7. Scenario objective flow.
8. Hazard detection and trainee action tracking.
9. PPE selection and inspection logic.
10. Local scoring and immediate feedback.
11. Local session persistence.
12. Offline queue for unsent training data.
13. Secure HTTPS communication with the backend.
14. Sync status and retry handling.
15. Production build packaging for target devices.

The VR client must not directly access the database. It must communicate only through backend API endpoints.

---

## 5. Target Production Platforms

## 5.1 Primary Platform

Primary production target:

- Meta Quest 3
- Meta Quest 3S if performance testing confirms stable quality

Standalone Quest support is important because training centers and construction companies need a practical setup. A standalone headset is easier to deploy than a PC VR setup.

## 5.2 Secondary Platform

Secondary target:

- PC VR through OpenXR

PC VR can be used for high-quality presentations, internal testing, content review, and customers who already operate PC VR labs.

## 5.3 Runtime Direction

Production runtime direction:

- Unreal Engine 5.6 or the approved production engine version;
- OpenXR as the main VR runtime;
- Android ASTC packaging for Quest;
- production signing configuration;
- versioned releases;
- device-tested builds, not editor-only validation;
- scalable quality settings.

---

## 6. Production Training Package

The initial production release should contain a focused but complete training package. It should not be described as a temporary prototype. It should be a real first commercial package that can be shown, tested, and sold to early customers.

Initial production package name:

**BuildSafe VR — Construction Hazard Recognition Package**

Initial production modules:

1. **PPE & Site Entry Check**
2. **Work at Height / Fall Hazard Recognition**
3. **Construction Site Hazard Hunt**

These three modules are enough to create a complete production workflow:

- trainee enters the system;
- trainee selects or receives assigned training;
- trainee completes realistic tasks;
- trainee receives feedback;
- result is synced to server;
- manager receives report.

---

## 7. Production User Flow

A production training session should work as follows:

1. The trainer prepares the headset.
2. The trainee puts on the VR headset.
3. The application opens in a clean kiosk-style training mode.
4. The trainee selects language.
5. The trainee logs in, enters a training PIN, or scans a QR code.
6. The application validates access with the backend or uses an approved offline assignment.
7. The assigned training module appears.
8. The trainee starts the module.
9. The tutorial explains controls, objectives, and safety interaction rules.
10. The trainee completes the training scenario.
11. The application records important events.
12. The application calculates score and shows feedback.
13. The session is saved locally.
14. The session is uploaded to the backend.
15. If upload fails, the session remains in the offline queue.
16. The trainer or safety manager can later review the result in the dashboard.

The flow must be simple enough for a first-time VR user.

---

## 8. Module 1 — PPE & Site Entry Check

## 8.1 Purpose

This module verifies whether the trainee understands basic site entry preparation. Before entering a construction site, the trainee must select required PPE, inspect equipment condition, read warning signs, and enter through the correct safe path.

## 8.2 Production Scene Requirements

The scene should include:

- jobsite entry gate;
- PPE preparation table;
- hard hat;
- safety glasses;
- gloves;
- high-visibility vest;
- safety boots;
- harness;
- damaged harness option;
- damaged helmet option if needed;
- warning signs;
- restricted area sign;
- toolbox talk board;
- safe entry route;
- blocked or unsafe entry route.

## 8.3 Required Trainee Actions

The trainee must:

1. Select correct PPE.
2. Inspect PPE condition.
3. Reject damaged PPE.
4. Read or acknowledge required signs.
5. Avoid restricted areas.
6. Enter through the correct route.
7. Confirm readiness to begin work.

## 8.4 Tracked Events

The client should record:

- `module_started`
- `ppe_selected`
- `required_ppe_missing`
- `damaged_ppe_selected`
- `damaged_ppe_rejected`
- `warning_sign_checked`
- `restricted_area_entered`
- `safe_entry_completed`
- `feedback_shown`
- `module_completed`

## 8.5 Feedback Rules

Feedback must be direct, clear, and professional. It should explain what happened, why it matters, and what the trainee should do differently.

Example:

> You selected a damaged harness. Damaged fall protection equipment must not be used. Choose approved equipment in good condition before working at height.

No graphic accident visuals should be used.

---

## 9. Module 2 — Work at Height / Fall Hazard Recognition

## 9.1 Purpose

This module trains the trainee to identify fall hazards, unsafe ladder conditions, missing guardrails, unsafe edges, and fall protection requirements.

## 9.2 Production Scene Requirements

The scene should include:

- scaffold platform;
- ladder;
- open edge;
- correct guardrail;
- missing guardrail;
- anchor point;
- harness equipment;
- toe board;
- falling object risk area;
- NPC worker with unsafe behavior;
- unsafe ladder angle;
- clearly marked work zones.

## 9.3 Required Trainee Actions

The trainee must:

1. Identify open-edge hazards.
2. Identify missing guardrails.
3. Check ladder placement.
4. Identify where fall protection is required.
5. Select or confirm correct fall protection equipment.
6. Report unsafe NPC behavior.
7. Complete the scenario checklist.

## 9.4 Tracked Events

The client should record:

- `hazard_found`
- `hazard_missed`
- `unsafe_zone_entered`
- `ladder_checked`
- `guardrail_checked`
- `anchor_point_checked`
- `worker_hazard_reported`
- `checklist_completed`
- `critical_error_triggered`
- `module_completed`

## 9.5 Safety UX Rule

If the trainee makes a critical mistake, the application should stop the unsafe action, fade or pause the scene, and show an explanation. The experience should teach, not scare.

---

## 10. Module 3 — Construction Site Hazard Hunt

## 10.1 Purpose

This module tests general hazard recognition across a realistic construction site. The trainee must inspect multiple zones and identify hazards within the scenario rules.

## 10.2 Production Scene Zones

The scene should include:

- pedestrian route;
- material storage area;
- electrical area;
- trench or excavation area;
- scaffold area;
- equipment movement area;
- loading zone;
- emergency path.

## 10.3 Example Hazards

The trainee may need to identify:

- cable across walkway;
- open trench without barrier;
- improperly stacked materials;
- worker without high-visibility vest;
- moving equipment without spotter;
- wet or slippery floor;
- open electrical panel;
- unsecured ladder;
- falling object risk;
- blocked emergency path;
- missing warning sign;
- poor housekeeping area.

## 10.4 Tracked Events

For each hazard, the application should track:

- hazard ID;
- hazard category;
- severity;
- whether the trainee found it;
- time found;
- whether a hint was used;
- wrong object selections;
- unsafe zone entry;
- final hazard status.

## 10.5 Completion Result

At the end, the trainee should see:

- final score;
- pass/fail result;
- hazards found;
- hazards missed;
- critical hazards missed;
- unsafe actions;
- time used;
- recommendation.

---

## 11. Production Scenario System

The scenario system must be data-driven and maintainable. A developer or technical designer should be able to add new hazards, scoring rules, and feedback without rewriting core systems every time.

Recommended structure:

- C++ base systems for stability;
- Blueprint-friendly components for content setup;
- Unreal Data Assets for module definitions;
- Unreal Data Assets or JSON for hazard definitions;
- localization keys for all user-facing text;
- versioned module codes;
- server-compatible identifiers.

## 11.1 Module Definition

Each module should define:

- module code;
- module title;
- module version;
- supported languages;
- objective list;
- required hazards;
- optional hazards;
- critical fail conditions;
- pass threshold;
- scoring rules;
- feedback messages;
- backend mapping code.

## 11.2 Hazard Definition

Each hazard should define:

- hazard code;
- hazard title;
- hazard category;
- severity;
- correct action type;
- feedback localization key;
- score penalty;
- whether it is critical;
- analytics category;
- backend event code.

---

## 12. Production Unreal Architecture

## 12.1 Required Systems

### `UTrainingSessionSubsystem`

Responsible for:

- starting a training session;
- ending a training session;
- storing current session state;
- collecting event records;
- calculating local score;
- preparing data for server sync;
- preventing data loss during level transition or app pause.

### `UScenarioManagerComponent`

Responsible for:

- loading the selected module;
- starting scenario stages;
- tracking objectives;
- validating completion;
- triggering feedback;
- ending the module.

### `UHazardInteractionComponent`

Attached to hazard actors.

Responsible for:

- storing hazard code;
- storing severity;
- handling trainee selection;
- validating correct interaction;
- sending events to the session subsystem;
- showing hazard-specific feedback.

### `UPPEItemComponent`

Attached to PPE objects.

Responsible for:

- item type;
- required/optional status;
- item condition;
- selected state;
- damaged state;
- validation rules.

### `UTrainingApiClient`

Responsible for:

- HTTPS calls to the backend;
- auth token handling;
- session start requests;
- event batch upload;
- session completion upload;
- retry-safe request handling;
- readable API errors.

### `UOfflineSyncSubsystem`

Responsible for:

- local session queue;
- retry scheduling;
- sync status;
- duplicate upload prevention;
- local persistence until server acknowledgement.

### `ULocalizationManager`

Responsible for:

- language selection;
- localized text lookup;
- localized feedback messages;
- future audio localization support.

---

## 13. Server Data Contract

The VR client must send structured training data. It must not send unnecessary private tracking information.

Do not send continuous head movement, hand movement, or raw body tracking by default. Only send training-relevant events.

## 13.1 Session Start Payload

The client should send:

- trainee ID or training code;
- company assignment if available;
- device ID;
- module code;
- module version;
- app version;
- language;
- client timestamp;
- client session ID for idempotency.

## 13.2 Training Event Payload

The client should send event batches containing:

- event type;
- hazard code;
- category;
- severity;
- action;
- correctness;
- time offset;
- metadata if needed.

## 13.3 Session Completion Payload

At completion, the client should send:

- client session ID;
- server session ID if already received;
- module code;
- module version;
- duration;
- final score;
- pass/fail status;
- hazards found;
- hazards missed;
- unsafe actions;
- hints used;
- app version;
- device ID;
- local completion timestamp.

---

## 14. Offline Mode Production Requirements

Offline mode is mandatory for production because training rooms may have weak or unstable internet.

The client must:

1. Save the session locally before sending to the server.
2. Keep a pending sync queue.
3. Retry failed uploads.
4. Never create duplicate records intentionally.
5. Keep completed sessions until the server confirms successful sync.
6. Show clear sync status to trainer/admin screens.
7. Avoid storing unnecessary personal data locally.
8. Encrypt or protect local sensitive data when practical for the target platform.

If the user completes training offline, the result must not be lost.

---

## 15. Scoring Requirements

The scoring system must be deterministic, explainable, and versioned.

Initial scoring model:

- start score: 100;
- missed critical hazard: -15;
- missed medium hazard: -8;
- missed minor hazard: -3;
- unsafe action: -20;
- hint used: -5;
- timeout: -10.

Default pass threshold: 80.

Production requirement: scoring rules must be associated with a module version. If module content changes, historical reports must still be understandable.

---

## 16. UI/UX Production Requirements

The interface must be usable by people who may never have used VR before.

Required screens:

1. Startup/loading screen.
2. Language selection.
3. Login/PIN/QR access screen.
4. Device sync status screen.
5. Module assignment screen.
6. Tutorial screen.
7. Objective checklist.
8. In-world hazard feedback panel.
9. Pause menu.
10. End-of-session result screen.
11. Upload/sync result status.
12. Device reset/logout screen.

UI rules:

- large readable text;
- simple interaction zones;
- clear color contrast;
- no cluttered menus;
- no hidden critical actions;
- all errors must tell the user what to do next.

---

## 17. Localization Requirements

Production language support should be designed from day one.

Initial target languages:

1. English
2. Spanish

Future languages may include:

- Russian;
- Kyrgyz;
- Arabic;
- French.

All trainee-facing text must use localization keys. Avoid hardcoded strings in Blueprints or C++.

---

## 18. Performance Requirements

Production VR performance is a hard requirement.

Target:

- stable VR frame rate on supported Quest devices;
- no major hitches during training actions;
- fast scene loading where possible;
- predictable memory use;
- no editor-only assumptions.

Optimization rules:

- use optimized assets;
- use LODs;
- use baked lighting where practical;
- avoid heavy dynamic shadows;
- limit transparent materials;
- use simple collision;
- avoid unnecessary runtime physics;
- use texture atlases where useful;
- profile on real Quest hardware early and repeatedly.

Production builds must be tested on real devices, not only in Unreal Editor.

---

## 19. Security and Privacy Requirements

The VR client must follow these rules:

- use HTTPS for all backend communication;
- never hardcode production secrets;
- avoid storing passwords locally;
- store tokens safely where platform allows;
- support logout and device reset;
- collect only training-required data;
- do not collect unnecessary biometrics;
- do not send raw motion tracking by default;
- avoid exposing server URLs, tokens, or private config in public assets;
- handle API errors without leaking sensitive information.

---

## 20. Release and Build Requirements

Production releases must be versioned and traceable.

Every release should have:

- app version;
- build number;
- target platform;
- backend API compatibility version;
- module content version;
- release notes;
- known issues;
- tested device list;
- signed package where required.

Recommended branches:

- `main` for stable production-ready code;
- `develop` for active integration if needed;
- feature branches for new modules or systems;
- release tags for shipped builds.

---

## 21. Quality Assurance Requirements

Before any production release, test:

1. headset startup;
2. login/PIN/QR flow;
3. module loading;
4. all training objectives;
5. all critical hazards;
6. scoring correctness;
7. feedback messages;
8. offline completion;
9. retry sync;
10. backend upload;
11. session result visibility in dashboard;
12. localization text;
13. app pause/resume;
14. headset restart after unsynced session;
15. performance on target hardware.

A release should not be considered production-ready if a completed training session can be lost.

---

## 22. Production Development Roadmap

## Release 1 — Production Foundation

Goal: create a real end-to-end training product.

Required deliverables:

- Unreal VR project configured for Quest and OpenXR;
- production-ready project structure;
- core interaction system;
- training session subsystem;
- scenario manager;
- hazard interaction component;
- PPE item component;
- scoring system;
- offline sync subsystem;
- backend API client;
- result screen;
- first three training modules;
- Quest production build;
- backend sync verified.

## Release 2 — Training Operations

Goal: make the product easier to use by trainers.

Deliverables:

- improved headset login flow;
- trainer/device status screen;
- stronger offline sync visibility;
- better module assignment handling;
- improved localization;
- production QA checklist automation where possible.

## Release 3 — Customer Customization

Goal: support paid customer-specific training content.

Deliverables:

- custom scenario configuration;
- client-branded module options;
- configurable hazards;
- configurable pass thresholds;
- support for additional module packs.

---

## 23. Production Acceptance Criteria

The VR client is production-ready when:

1. A trainee can complete assigned training without developer assistance.
2. The app works on target Quest hardware.
3. The app records training events correctly.
4. The app calculates score correctly.
5. The app saves results locally before upload.
6. The app syncs completed sessions to the backend.
7. The app survives internet loss without losing completed results.
8. The dashboard can display the uploaded session.
9. The report generated by the server matches the session result.
10. The release is versioned and tested.

---

## 24. Final Summary

This repository is the production VR client for BuildSafe VR. Its job is to deliver a reliable construction safety training experience in VR and send measurable training results to the backend.

The first commercial direction is clear:

**A trainee enters a VR construction site, completes safety training tasks, identifies hazards, receives professional feedback, and sends a reliable training result to the server for supervisor review and reporting.**

This project must be built from the beginning as a real product: stable, secure, measurable, maintainable, and ready for customer use.