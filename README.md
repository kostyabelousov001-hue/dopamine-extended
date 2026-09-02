# Dopamine Extended

Dopamine jailbreak with ClearSword exploit for iOS 18.7.3 on iPhone XS (A12).

## Features
- Integrated ClearSword exploit (CVE-2025-43520)
- iOS 18.7.3 support for A12 devices
- "Extended!" subtitle in UI
- GitHub Actions for automated builds

## Supported Devices
- iPhone XS (A12)
- iPhone XR (A12)
- iPhone SE 2020 (A13)

## Supported iOS Versions
- iOS 15.0 - 26.0.1

## Building

### Prerequisites
- macOS 13+
- Xcode 15.4+
- ldid
- darling

### Build Steps
```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/dopamine-extended.git
cd dopamine-extended

# Build
make clean
make
```

### GitHub Actions
The repository includes GitHub Actions workflow that:
- Builds on macOS 14
- Uses Xcode 15.4
- Creates release with IPA file

## Installation
1. Download the latest IPA from Releases
2. Sideload using AltStore, Sideloadly, or similar
3. Open Dopamine app
4. Tap "Jailbreak"

## Credits
- [opa334](https://github.com/opa334) - Original Dopamine
- [TheRealClarity](https://github.com/TheRealClarity) - ClearSword exploit

## License
MIT License
