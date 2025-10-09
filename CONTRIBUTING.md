# Contributing to ESPHome LVGL Projects

Thank you for your interest in contributing! This document provides guidelines for contributing to this repository.

## 🎯 Types of Contributions

We welcome several types of contributions:

### 1. Bug Reports
- Use GitHub Issues
- Include ESPHome version
- Provide YAML configuration (remove secrets)
- Describe expected vs actual behavior
- Include relevant logs

### 2. Bug Fixes
- Fix existing issues
- Test thoroughly before submitting
- Document what was fixed

### 3. New Features
- Discuss in an issue first
- Keep backwards compatibility when possible
- Update documentation
- Add to changelog

### 4. Documentation
- Fix typos, improve clarity
- Add examples
- Update outdated information
- Add troubleshooting tips

### 5. Hardware Ports
- New device configurations
- Pin mapping documentation
- Hardware compatibility notes
- Testing results

## 🔧 Development Guidelines

### Code Quality
- **YAML Formatting**: Follow ESPHome style guide
- **Comments**: Add clear comments for complex sections
- **Configuration**: Use substitutions for entity IDs
- **Secrets**: Never commit secrets.yaml files
- **Naming**: Use descriptive names for components

### Testing Requirements
- Test on actual hardware
- Verify all features work
- Check Home Assistant integration
- Document any limitations

### Documentation Requirements
- Update README.md if adding features
- Include setup instructions
- Add troubleshooting section
- Document breaking changes

## 📝 Pull Request Process

### 1. Before You Start
- Check if issue exists
- Discuss major changes first
- Fork the repository
- Create a feature branch

### 2. Making Changes
```bash
# Fork and clone
git clone https://github.com/YOUR_USERNAME/ESPHome-Projects.git
cd ESPHome-Projects

# Create feature branch
git checkout -b feature/your-feature-name

# Make changes
# Test thoroughly

# Commit with clear message
git commit -m "Add: Brief description of change"
```

### 3. Commit Message Format
```
Type: Brief description

Longer description if needed

- Bullet points for details
- What changed
- Why it changed
- How to use new feature
```

**Types:**
- `Add:` New feature or file
- `Fix:` Bug fix
- `Update:` Modify existing feature
- `Docs:` Documentation changes
- `Refactor:` Code restructuring
- `Test:` Add or update tests

### 4. Submit Pull Request
- Clear title and description
- Reference related issues
- Include testing details
- Add screenshots for UI changes
- Update documentation

### 5. Review Process
- Maintainers will review
- Address feedback
- Make requested changes
- Be patient and respectful

## 🧪 Testing Checklist

Before submitting, verify:

- [ ] Code compiles without errors
- [ ] All features work as expected
- [ ] No new warnings in logs
- [ ] Home Assistant integration works
- [ ] Touch controls respond correctly
- [ ] Display shows correctly
- [ ] Voice assistant works (if applicable)
- [ ] Battery monitoring works (if applicable)
- [ ] Documentation updated
- [ ] No secrets committed

## 📋 Project-Specific Guidelines

### Ball V5.3 (Active Development)
- This is the main project
- Focus on stability
- Maintain backwards compatibility
- Comprehensive testing required
- Update all relevant docs

### SMARTRING V1 (Experimental)
- More experimental changes allowed
- Document hardware differences
- Note what works vs what needs testing
- Help with audio configuration welcome

### Legacy Projects
- Only critical bug fixes
- Direct users to current version
- No new features

## 🚫 What NOT to Contribute

- **Secrets**: Never commit passwords, API keys, etc.
- **Breaking Changes**: Without discussion
- **Incomplete Features**: Test before submitting
- **Vendor Libraries**: Don't add large dependencies
- **Binary Files**: Avoid committing binaries
- **Personal Configs**: Keep personal setup details private

## 📚 Resources

### ESPHome
- [ESPHome Documentation](https://esphome.io)
- [ESPHome Discord](https://discord.gg/KhAMKrd)
- [ESPHome GitHub](https://github.com/esphome/esphome)

### LVGL
- [LVGL Documentation](https://docs.lvgl.io/)
- [LVGL Forum](https://forum.lvgl.io/)
- [LVGL GitHub](https://github.com/lvgl/lvgl)

### Home Assistant
- [Home Assistant Docs](https://www.home-assistant.io/docs/)
- [Home Assistant Community](https://community.home-assistant.io/)

## 🎖️ Recognition

Contributors will be:
- Listed in project credits
- Mentioned in relevant changelogs
- Appreciated by the community!

## ❓ Questions?

- Check existing documentation first
- Search closed issues
- Open a discussion issue
- Ask in ESPHome Discord

## 📜 Code of Conduct

### Our Pledge
We are committed to providing a welcoming and inspiring community for all.

### Our Standards
- Be respectful and inclusive
- Accept constructive criticism gracefully
- Focus on what's best for the community
- Show empathy towards others

### Unacceptable Behavior
- Harassment or discriminatory comments
- Trolling or insulting comments
- Publishing others' private information
- Other unprofessional conduct

## 📄 License

By contributing, you agree that your contributions will be licensed under the same license as the project.

---

**Thank you for contributing to ESPHome LVGL Projects!** 🎉

Your contributions help make these projects better for everyone.
