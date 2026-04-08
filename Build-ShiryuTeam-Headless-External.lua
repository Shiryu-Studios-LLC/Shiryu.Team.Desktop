-- ShiryuTeam-Headless-External.lua

IncludeDir = {}
IncludeDir["glm"] = "../vendor/glm"
IncludeDir["spdlog"] = "../vendor/spdlog/include"

group "Dependencies"
   include "vendor/yaml-cpp"
group ""

group "Core"
    include "ShiryuTeam/Build-ShiryuTeam-Headless.lua"

    -- Optional modules
    if os.isfile("ShiryuTeam-Modules/ShiryuTeam-Networking/Build-ShiryuTeam-Networking.lua") then
        include "ShiryuTeam-Modules/ShiryuTeam-Networking/Build-ShiryuTeam-Networking.lua"
    end
group ""