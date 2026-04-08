# ShiryuTeam.Launcher

The central hub for the ShiryuTeam Ecosystem - launch and manage all your ShiryuTeam apps from one place.

## Overview

ShiryuTeam.Launcher is the main desktop application that provides:
- **Authentication** - Login to your ShiryuTeam account
- **App Catalog** - Browse available ShiryuTeam apps
- **App Management** - Install, launch, and manage your apps
- **Settings** - Configure your launcher preferences

## Related Repos

- [ShiryuTeam.Api](https://github.com/Shiryu-Studios-LLC/ShiryuTeam.Api) - Backend API (Cloudflare Workers)
- [ShiryuTeam.Dev](https://github.com/Shiryu-Studios-LLC/ShiryuTeam.Dev) - Development environment app
- [ShiryuTeam.Projects](https://github.com/Shiryu-Studios-LLC/ShiryuTeam.Projects) - Project management app
- [ShiryuTeam.Cloud](https://github.com/Shiryu-Studios-LLC/ShiryuTeam.Cloud) - Cloudflare management app
- [ShiryuTeam.Teams](https://github.com/Shiryu-Studios-LLC/ShiryuTeam.Teams) - Team collaboration app

## Tech Stack

- **C++** with ShiryuTeam framework
- **Vulkan** for rendering
- **Dear ImGui** for UI
- **Cloudflare Workers** for backend API

## Requirements

- [Visual Studio 2026](https://visualstudio.com)
- [Vulkan SDK](https://vulkan.lunarg.com/sdk/home#windows)

## Getting Started

1. Clone the repository
2. Run `scripts/Setup-Project.ps1` to generate Visual Studio project files
3. Open the solution and build the Shiryu.Launcher project

## Architecture

```
Shiryu.Launcher ──▶ Cloudflare API (Shiryu.Api)
                      │
                      ├── App Registry
                      ├── Authentication
                      └── Database
```

## License

Proprietary - Shiryu Studios LLC