# ⚠️ DEPRECATED: Ball V5.2

**This version is deprecated and no longer maintained.**

## 🎯 Use Ball V5.3 Instead

Ball V5.3 is the latest version with improvements over V5.2:

- ✅ Live album art display (NEW!)
- ✅ Fixed button overlap issues
- ✅ Better touch zone accuracy
- ✅ Removed non-functional camera page
- ✅ Simplified navigation
- ✅ Fixed 'None' error in brightness sensor
- ✅ Updated documentation

## 📚 Documentation

**Current Version:** [Ball_v5.3/README.md](../Ball_v5.3/README.md)

**Quick Start:** [Ball_v5.3/QUICK_START.md](../Ball_v5.3/QUICK_START.md)

**What's New in V5.3:** [Ball_v5.3/CHANGES_V5.3.md](../Ball_v5.3/CHANGES_V5.3.md)

## ⚡ Easy Migration from V5.2

V5.3 is mostly backward compatible with V5.2:

```bash
cd ../Ball_v5.3

# 1. Copy your secrets (if you have one)
cp ../Ball_v5.2/secrets.yaml .

# 2. Update entity IDs in Ball_v5.3.yaml (same as V5.2)
# Remove camera_entity (no longer needed)

# 3. Flash
esphome run Ball_v5.3.yaml
```

**Changes needed:**
- Remove `camera_entity` from substitutions (no longer needed)
- All other settings remain the same

---

**This folder is kept for historical reference only.**
