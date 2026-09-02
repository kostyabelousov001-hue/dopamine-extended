# How to Push to GitHub

## Option 1: Manual Upload via GitHub Website

1. Go to https://github.com/new
2. Create repository:
   - Name: `dopamine-extended`
   - Description: `Dopamine jailbreak with ClearSword exploit for iOS 18.7.3`
   - Select **Public**
   - Click **Create repository**

3. Upload files:
   - Click "uploading an existing file"
   - Drag and drop all files from `C:\Users\user\AppData\Local\Temp\opencode\darksword-exploit\dopamine-clearsword`
   - Click **Commit changes**

## Option 2: Use GitHub Desktop

1. Download GitHub Desktop: https://desktop.github.com/
2. Clone the repository
3. Copy files
4. Commit and push

## Option 3: Use Different Network

The current network blocks port 443 (HTTPS). Try:
- Different WiFi
- Mobile hotspot
- VPN

Then run:
```bash
cd C:\Users\user\AppData\Local\Temp\opencode\darksword-exploit\dopamine-clearsword
git remote add origin https://github.com/YOUR_USERNAME/dopamine-extended.git
git push -u origin master
```

## Files to Upload

The repository contains:
- ClearSword exploit integration
- Dopamine with "Extended!" subtitle
- GitHub Actions workflow
- iOS 18.7.3 offsets for A12
