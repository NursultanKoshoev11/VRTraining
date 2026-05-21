# VRTraining — BuildSafe VR Client Project Overview

## 1. Project Summary

**VRTraining** is the Unreal Engine client application for a VR construction safety training product. The goal of this project is to create a realistic, practical, and measurable VR simulator where construction workers can learn how to recognize hazards, make safe decisions, complete training scenarios, and send training results to the backend server.

This repository contains the **VR client side** of the product. The client will run on VR devices such as Meta Quest and, later, PC VR headsets. The client is responsible for the immersive training experience: the construction site environment, player interactions, safety tasks, scenario flow, scoring, local event collection, offline storage, and synchronization with the backend server.

The product should not be treated as a simple VR game. It is a **B2B training tool** for construction companies, safety training centers, vocational schools, community colleges, and apprenticeship programs. The main value is not only that the user can walk around a virtual construction site, but that the system can measure what the trainee did, what hazards they found, what mistakes they made, and whether they are ready for the next training step.

---

## 2. Product Vision

The vision is to build a VR training platform that helps construction teams train workers before they enter a real jobsite. In a real construction environment, mistakes can be expensive and dangerous. In VR, the trainee can make mistakes safely, receive instant feedback, repeat scenarios, and improve hazard recognition skills.

The first version should focus on **construction safety hazard recognition**. The trainee will enter a virtual jobsite, inspect equipment, identify dangerous conditions, choose correct safety actions, and complete scenario checklists.

The long-term vision is to turn this into a modular platform where new training modules can be added over time:

- PPE and site entry training
- Fall hazard recognition
- Scaffold safety awareness
- Trench and excavation awareness
- Electrical hazard awareness
- Struck-by hazard awareness
- Caught-in/between hazard awareness
- Equipment blind spot awareness
- Emergency evacuation practice
- Custom training scenes based on a client jobsite

---

## 3. Important Positioning Note

This product should be described as **supplemental VR safety training** or **OSHA-aligned hazard recognition practice**.

It should not be described as:

- official OSHA certification
- OSHA-approved training
- replacement for OSHA 10 or OSHA 30
- replacement for employer-required job-specific training
- guarantee that accidents will not happen

The VR application is intended to support training, practice, documentation, and readiness checks. Any formal safety compliance requirements must be reviewed with qualified safety professionals and legal/compliance advisors before the product is sold as part of a formal training program.

---

## 4. Role of This Repository

This repository is for the **Unreal Engine VR client**.

The VR client will be responsible for:

1. Rendering the virtual construction site.
2. Providing realistic VR interaction.
3. Running training scenarios.
4. Tracking user actions inside each scenario.
5. Calculating local score and progress.
6. Showing feedback to the trainee.
7. Saving training data locally if internet is unavailable.
8. Sending training results to the backend server.
9. Supporting multiple training modules.
10. Supporting future localization, for example English and Spanish.

The VR client should stay focused on training simulation and user experience. Long-term storage, reporting, company management, user management, and analytics belong to the server repository.

---

## 5. Target Platforms

### 5.1 Primary Platform

The primary target platform should be:

- Meta Quest 3
- Meta Quest 3S, if performance allows

The reason is simple: standalone headsets are easier for training centers and construction companies. A client does not need a powerful gaming PC for every headset.

### 5.2 Secondary Platform

Secondary platform:

- PC VR through OpenXR

This can be useful for demos, higher quality visuals, development testing, trade shows, and customers who already have PC VR hardware.

### 5.3 Engine Direction

Recommended engine direction:

- Unreal Engine 5.6 or the current stable Unreal version used by the team
- OpenXR as the main VR runtime
- Android ASTC build for Quest
- scalable graphics settings
- optimized assets for standalone VR

---

## 6. Core User Flow

The basic trainee flow should be:

1. The trainee puts on the VR headset.
2. The trainee selects language.
3. The trainee logs in or enters a training PIN/QR code.
4. The application downloads or loads assigned training modules.
5. The trainee selects a module.
6. The tutorial explains movement, interaction, and objective.
7. The trainee enters the VR construction scenario.
8. The trainee identifies hazards and performs required actions.
9. The application records training events.
10. The trainee finishes the scenario.
11. The application shows score, feedback, and missed hazards.
12. The result is saved locally and sent to the server.
13. The safety manager can later see the result in the web dashboard.

---

## 7. MVP Scope

The first MVP should be small, focused, and sellable. The MVP should not try to simulate every possible construction situation. The first goal is to prove that the product can deliver a valuable VR training session and a useful report.

### MVP Name

**BuildSafe VR — Focus Four Starter Pack**

### MVP Modules

The first version should include three VR modules:

1. **PPE & Site Entry Check**
2. **Work at Height / Fall Hazard Recognition**
3. **Construction Site Hazard Hunt**

### MVP Technical Features

The VR client MVP should include:

- VR locomotion or guided teleport movement
- hand interaction
- object selection
- hazard marking system
- scenario objectives
- scoring system
- local event tracking
- end-of-session feedback screen
- backend sync
- offline queue for unsent results
- basic language support structure

---

## 8. Module 1 — PPE & Site Entry Check

### Purpose

This module teaches and tests whether the trainee understands basic site entry safety behavior. Before entering a construction site, the trainee must choose correct PPE, inspect it, understand warning signs, and enter through a safe path.

### Scene Description

The trainee starts near the entrance of a construction site. In front of the trainee there is a small preparation area with safety equipment and signs.

Objects in the scene:

- hard hat
- safety glasses
- gloves
- high-visibility vest
- safety boots
- harness
- damaged harness option
- warning signs
- restricted area sign
- toolbox talk board
- safe entry gate
- unsafe entry path

### Required Trainee Actions

The trainee should:

1. Select required PPE.
2. Inspect whether the PPE is damaged.
3. Reject damaged equipment.
4. Read warning signs.
5. Choose the correct site entry path.
6. Confirm readiness to begin work.

### Events to Track

The client should track events such as:

- `ppe_selected`
- `ppe_missing`
- `damaged_ppe_selected`
- `warning_sign_checked`
- `restricted_area_entered`
- `safe_entry_completed`
- `module_completed`

### Feedback Examples

If the trainee selects a damaged harness, the application should explain that damaged fall protection equipment must not be used.

If the trainee enters the restricted area, the scenario should pause and explain why that path is unsafe.

The feedback should be direct, calm, and professional. It should teach the trainee without making the training feel like a punishment.

---

## 9. Module 2 — Work at Height / Fall Hazard Recognition

### Purpose

This module teaches the trainee to identify fall hazards and unsafe working conditions at height.

### Scene Description

The trainee is placed in a jobsite area with scaffolding, ladders, open edges, guardrails, anchor points, and workers performing tasks.

Objects and areas:

- scaffold platform
- ladder
- open edge
- guardrail
- missing guardrail
- anchor point
- harness
- toe board
- falling object zone
- worker without correct PPE
- unsafe ladder angle

### Required Trainee Actions

The trainee should:

1. Identify missing guardrails.
2. Identify unsafe open edges.
3. Check ladder placement.
4. Identify where fall protection is required.
5. Select correct safety equipment.
6. Mark unsafe behavior by NPC workers.
7. Complete a safety checklist before work begins.

### Events to Track

The client should track:

- `hazard_found`
- `hazard_missed`
- `unsafe_zone_entered`
- `ladder_checked`
- `guardrail_checked`
- `anchor_point_checked`
- `worker_hazard_reported`
- `checklist_completed`

### UX Rule

The module should not show graphic injuries or frightening accident visuals. If the trainee makes a critical mistake, the scene can stop, fade, or show a warning panel. The focus should be professional training, not shock value.

---

## 10. Module 3 — Construction Site Hazard Hunt

### Purpose

This module tests general hazard recognition across a construction site. The trainee must walk through the scene and identify as many hazards as possible within a time limit or objective list.

### Scene Description

The site should include multiple zones:

- material storage area
- pedestrian path
- electrical area
- trench area
- scaffold area
- moving equipment area
- loading zone

### Example Hazards

The trainee may need to identify:

- cable across walkway
- open trench without barrier
- improperly stacked materials
- worker without high-visibility vest
- moving equipment without spotter
- wet/slippery floor
- open electrical panel
- unsecured ladder
- falling object risk
- blocked emergency path
- missing warning sign
- poor housekeeping area

### Events to Track

The client should track:

- hazard ID
- hazard category
- severity
- whether the trainee found it
- time when it was found
- whether the trainee used a hint
- whether the trainee clicked the wrong object
- whether the trainee entered an unsafe area

### End Result

At the end of the module, the trainee should see:

- total score
- hazards found
- hazards missed
- critical hazards missed
- unsafe actions
- time used
- recommendation to repeat or proceed

---

## 11. Scenario System Design

The training modules should be data-driven as much as possible. This means a developer should be able to create new hazards and scenario steps without hardcoding every rule in C++.

Recommended approach:

- Unreal Data Assets for module definitions
- Data Assets or JSON for hazard definitions
- Blueprint-friendly components for designers
- C++ base classes for core logic
- clear separation between scenario logic and visual content

### Example Scenario Data

Each scenario can define:

- module ID
- module title
- objective list
- required hazards
- optional hazards
- fail conditions
- pass threshold
- time limit
- feedback messages
- backend module code

### Example Hazard Data

Each hazard should have:

- hazard code
- hazard category
- severity
- correct action type
- feedback text
- score penalty
- whether it is critical
- localization key

---

## 12. Recommended Unreal Architecture

### 12.1 Core Classes and Systems

The project should eventually include these systems:

#### `UTrainingSessionSubsystem`

Responsible for:

- starting a training session
- ending a training session
- keeping current session state
- collecting training events
- calculating basic score
- sending final result to sync system

#### `UScenarioManagerComponent`

Responsible for:

- loading a module
- starting scenario stages
- checking objectives
- controlling scenario progression
- triggering final result screen

#### `UHazardInteractionComponent`

Attached to interactive hazard objects.

Responsible for:

- storing hazard ID
- storing hazard severity
- handling player selection
- checking if the action is correct
- sending event to training session system
- showing feedback

#### `UPPEItemComponent`

Attached to PPE objects.

Responsible for:

- item type
- item condition
- whether it is required
- whether it is selected
- whether it is damaged

#### `UReportSyncSubsystem`

Responsible for:

- sending sessions to backend
- retrying failed requests
- storing offline results
- confirming successful upload

#### `UTrainingApiClient`

Responsible for:

- HTTP requests to backend
- authentication token handling
- session start request
- event upload request
- session complete request
- error handling

---

## 13. Data Sent to the Server

The VR client should send useful training data, not unnecessary private tracking data.

The client should not send continuous head movement, hand movement, or body tracking unless there is a specific training reason and privacy review.

### Session Start Data

When a module starts, send:

- trainee ID or training code
- device ID
- module ID
- app version
- language
- timestamp

### Training Event Data

During the module, record events like:

- hazard found
- hazard missed
- unsafe action
- PPE selected
- damaged PPE selected
- checklist item completed
- hint used
- wrong object selected

### Session Completion Data

At the end, send:

- session ID
- module ID
- duration
- final score
- pass/fail status
- hazards found
- hazards missed
- unsafe actions
- hints used
- final event list or event summary

---

## 14. Offline Mode

Offline mode is important because a VR headset may be used in a training room with weak Wi-Fi.

The client should behave like this:

1. If internet is available, send data normally.
2. If internet is unavailable, save session data locally.
3. Mark the session as `pending_sync`.
4. Retry upload later.
5. Do not lose completed training data.
6. Show simple sync status to the trainer if needed.

Local storage should be structured and safe. Do not store sensitive data unnecessarily.

---

## 15. Scoring Design

The scoring system should be simple at first.

Example:

- start score: 100
- missed critical hazard: -15
- missed medium hazard: -8
- missed minor hazard: -3
- unsafe action: -20
- hint used: -5
- timeout: -10

Pass threshold can be 80 by default.

The scoring rules should be configurable per module later.

---

## 16. Feedback Design

Feedback is one of the most important parts of the training.

Good feedback should answer:

1. What happened?
2. Why is it unsafe?
3. What should the trainee do next time?

Example feedback:

> You selected a damaged harness. Damaged fall protection equipment should not be used. Choose approved equipment in good condition before working at height.

The tone should be professional and educational. Avoid overly dramatic language.

---

## 17. UI/UX Requirements

The UI should be very simple because VR users may be beginners.

Required UI screens:

1. Language selection
2. Login / PIN code entry
3. Module selection
4. Tutorial screen
5. Objective checklist
6. Hazard feedback panel
7. Pause menu
8. End-of-session result screen
9. Sync status screen

### Result Screen Should Show

- score
- pass/fail
- hazards found
- hazards missed
- unsafe actions
- time used
- recommendation

---

## 18. Localization

The application should be prepared for multiple languages from the beginning.

Initial language priority:

1. English
2. Spanish

Later possible languages:

- Russian
- Kyrgyz
- Arabic
- French

All user-facing training text should use localization keys, not hardcoded strings.

---

## 19. Performance Requirements

Because the target platform is standalone VR, performance is critical.

The application should target stable VR performance. Practical rules:

- use optimized assets
- use baked lighting where possible
- avoid heavy dynamic shadows
- use LODs
- use simple collision
- avoid unnecessary physics simulation
- reduce transparent materials
- limit post-processing
- use texture atlases where possible
- test on real Quest hardware early

The first MVP should prioritize stable training experience over photorealism.

---

## 20. Art and Environment Direction

The visual style should be realistic enough for training, but not too expensive to produce.

Recommended direction:

- realistic construction site layout
- clean readable hazards
- clear safety signs
- believable equipment
- optimized modular assets
- strong visual contrast for important objects
- avoid clutter that confuses training objectives

The environment should be built in a modular way so new training zones can be added later.

---

## 21. Integration With Backend

The VR client communicates with the server through HTTPS API.

Basic integration flow:

1. Client authenticates or uses training code.
2. Client requests assigned modules if needed.
3. Client starts a training session.
4. Client records local events.
5. Client sends event batch or final event summary.
6. Client completes the session.
7. Server stores the result.
8. Dashboard displays the result.

The client should not directly access the database. All communication must go through the backend API.

---

## 22. Security and Privacy Principles

The VR client should follow these principles:

- collect only data needed for training reports
- do not collect unnecessary biometric or motion history
- use HTTPS for server communication
- do not hardcode production secrets in the project
- store tokens securely where possible
- support logout or reset device flow
- avoid exposing server credentials in Blueprints or config files

---

## 23. Development Roadmap

### Phase 1 — Prototype

Goal: prove basic VR interaction and hazard detection.

Tasks:

- create Unreal VR project
- configure OpenXR
- set up Quest build pipeline
- create simple construction test scene
- implement object selection
- implement hazard component
- implement event logging in memory
- create result screen

### Phase 2 — MVP Training Modules

Goal: create the first playable training experience.

Tasks:

- build PPE module
- build work-at-height module
- build hazard hunt module
- implement scenario manager
- implement scoring
- implement feedback UI
- add tutorial

### Phase 3 — Backend Sync

Goal: send real results to server.

Tasks:

- implement API client
- start session endpoint integration
- complete session endpoint integration
- offline queue
- retry logic
- sync status UI

### Phase 4 — Pilot Build

Goal: prepare a demo for real customers.

Tasks:

- optimize for Quest
- record demo video
- create sample training flow
- test with multiple users
- verify reports in dashboard
- prepare pilot package

---

## 24. Definition of Done for the First Demo

The first demo can be considered ready when:

1. A trainee can enter VR.
2. A trainee can complete at least one safety module.
3. The module records correct and incorrect actions.
4. The trainee receives score and feedback.
5. The app sends the result to the server.
6. The result appears in the dashboard.
7. A report can be generated from the server side.
8. The Quest build runs smoothly enough for a demo.

---

## 25. Long-Term Product Direction

After MVP, the VR client can grow into a complete training platform with:

- more modules
- client-specific custom sites
- trainer mode
- multiplayer instructor observation
- voice guidance
- AI assistant for training feedback
- analytics-driven retraining recommendations
- downloadable training content packages
- headset kiosk mode
- LMS integration through server-side features

---

## 26. Final Summary

This repository is the foundation of the immersive training experience. The VR app should be clear, reliable, optimized, and measurable. The first goal is not to build the biggest possible simulator. The first goal is to build a focused product that demonstrates real value:

**A trainee enters a VR construction site, identifies hazards, makes decisions, receives feedback, and sends a measurable result to the backend for supervisor review.**

That is the core of the product.