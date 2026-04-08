# Shiryu Ecosystem Architecture

## Overview

Build a Creative Cloud-style platform with a central launcher and modular apps.

---

## Architecture Layers

```
┌─────────────────────────────────────────────────────────────┐
│                    Shiryu Launcher                         │
│         (Electron/Tauri - Desktop Application)              │
├─────────────────────────────────────────────────────────────┤
│  ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌─────────────────┐  │
│  │  Home   │  │  Apps   │  │Installed│  │    Settings    │  │
│  └─────────┘  └─────────┘  └─────────┘  └─────────────────┘  │
├─────────────────────────────────────────────────────────────┤
│                    WebView Container                         │
│         (Loads apps via URLs - web-based apps)              │
├─────────────────────────────────────────────────────────────┤
│                    Cloud Backbone                            │
│         (Cloudflare Workers + App Registry API)             │
└─────────────────────────────────────────────────────────────┘
```

---

## App Registry Schema

**Endpoint:** `GET /api/apps`

```json
{
  "apps": [
    {
      "id": "shiryu-dev",
      "name": "Shiryu Dev",
      "description": "Development environment with AI assistance",
      "version": "1.0.0",
      "icon": "dev-icon.png",
      "entry": "https://apps.shiryu.dev/dev",
      "category": "development",
      "permissions": ["file_access", "terminal"],
      "requiredRole": "developer",
      "enabled": true,
      "featured": true
    },
    {
      "id": "shiryu-projects",
      "name": "Shiryu Projects",
      "description": "Project and task management",
      "version": "1.0.0",
      "icon": "projects-icon.png",
      "entry": "https://apps.shiryu.dev/projects",
      "category": "productivity",
      "permissions": [],
      "enabled": true,
      "featured": true
    },
    {
      "id": "shiryu-cloud",
      "name": "Shiryu Cloud Manager",
      "description": "Manage Cloudflare deployments and workers",
      "version": "1.0.0",
      "icon": "cloud-icon.png",
      "entry": "https://apps.shiryu.dev/cloud",
      "category": "devops",
      "permissions": ["cloud_api"],
      "enabled": true,
      "featured": true
    }
  ],
  "categories": [
    "development",
    "productivity", 
    "devops",
    "communication",
    "design"
  ]
}
```

---

## Authentication Flow

```
┌─────────────┐     ┌─────────────────┐     ┌──────────────┐
│  Launcher   │────▶│  Auth Worker   │────▶│   Session   │
│  (login)    │     │  (validate)    │     │   (JWT)     │
└─────────────┘     └─────────────────┘     └──────────────┘
       │                                              │
       ▼                                              ▼
┌─────────────┐                             ┌──────────────┐
│  WebView    │────────────────────────────▶│  App (web)   │
│  (pass token)│                             │ (validates) │
└─────────────┘                             └──────────────┘
```

---

## Tech Stack

### Desktop (Launcher)
- **Electron** + React (fastest development)
- OR **Tauri** + React (lighter, more secure)

### Backend
- **Cloudflare Workers** (existing)
- **Durable Objects** (for real-time features later)

### Frontend Apps
- **React/Next.js**
- Hosted on Cloudflare Pages or Workers

---

## Implementation Phases

### Phase 1: Launcher Core
1. Set up Electron project
2. Create sidebar navigation (Home, Apps, Installed, Settings)
3. Add app registry fetch from API
4. Display app grid with icons
5. Click to load app in webview

### Phase 2: App System
1. Implement app installation (local state)
2. Add app categories and filtering
3. Search functionality
4. Featured apps section

### Phase 3: Authentication
1. Login flow in launcher
2. JWT token storage
3. Pass token to webview apps
4. Session validation in apps

### Phase 4: Advanced
1. App updates check
2. Role-based access
3. Settings sync
4. Offline mode

---

## Project Structure

```
Shiryu.Launcher/
├── src/
│   ├── main/           # Electron main process
│   │   ├── index.ts
│   │   ├── window.ts
│   │   └── ipc.ts
│   ├── renderer/       # React frontend
│   │   ├── App.tsx
│   │   ├── components/
│   │   │   ├── Sidebar.tsx
│   │   │   ├── AppGrid.tsx
│   │   │   ├── AppCard.tsx
│   │   │   └── WebView.tsx
│   │   ├── pages/
│   │   │   ├── Home.tsx
│   │   │   ├── Apps.tsx
│   │   │   ├── Installed.tsx
│   │   │   └── Settings.tsx
│   │   └── hooks/
│   │       └── useApps.ts
│   └── preload/        # Preload scripts
├── public/
├── package.json
└── electron-builder.json
```

---

## API Endpoints

### GET /api/apps
Returns all available apps from registry.

### GET /api/apps/:id
Returns single app details.

### GET /api/auth/login
Authenticate user and return JWT.

### GET /api/auth/validate
Validate JWT token.

---

## WebView Communication

```javascript
// In renderer (launcher)
window.electronAPI.openApp(appId, appUrl);

// In webview (app)
const token = new URLSearchParams(window.location.search).get('token');
// Use token for API calls
```

---

## Security Considerations

1. **Context Isolation** - Enable in Electron
2. **Node Integration** - Disable in renderer
3. **Web Security** - Enable for webview
4. **Token Storage** - Use secure storage (keytar)
5. **CSP** - Content Security Policy for webview

---

## Next Steps

1. Create new repo: `Shiryu.Launcher`
2. Initialize Electron + React project
3. Build sidebar and app grid
4. Connect to existing Cloudflare worker
5. Add webview loading
