# Shiryu.Launcher

The central hub for the Shiryu Ecosystem - launch and manage all your Shiryu apps from one place.

## Overview

Shiryu.Launcher is the main desktop application that provides:
- **Authentication** - Login to your Shiryu account
- **App Catalog** - Browse available Shiryu apps
- **App Management** - Install, launch, and manage your apps
- **Settings** - Configure your launcher preferences

## Related Repos

- [Shiryu.Api](https://github.com/Shiryu-Studios-LLC/Shiryu.Api) - Backend API (Cloudflare Workers)
- [Shiryu.Dev](https://github.com/Shiryu-Studios-LLC/Shiryu.Dev) - Development environment app
- [Shiryu.Projects](https://github.com/Shiryu-Studios-LLC/Shiryu.Projects) - Project management app
- [Shiryu.Cloud](https://github.com/Shiryu-Studios-LLC/Shiryu.Cloud) - Cloudflare management app
- [Shiryu.Teams](https://github.com/Shiryu-Studios-LLC/Shiryu.Teams) - Team collaboration app

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