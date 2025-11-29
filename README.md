# ksmaxis

A library for reading knob axis values using native OS APIs, designed for [ksm-v2](https://github.com/kshootmania/ksm-v2).

## Dependencies

| Platform | Input Type                           | Backend |
|----------|--------------------------------------|---------|
| Windows  | `kAnalogStick` / `kSlider` / `kMouse` | DirectInput 8 |
| macOS    | `kAnalogStick` / `kSlider` / `kMouse` | IOKit HID |
| Linux    | `kAnalogStick` / `kSlider`           | evdev |
| Linux    | `kMouse`                             | X11 XInput2 |

## Supported Input Modes

- `InputMode::kAnalogStick` - Analog Stick X/Y (circular)
- `InputMode::kSlider` - Slider input (circular)
- `InputMode::kMouse` - Mouse X/Y (relative)

## Build

```bash
cmake -B build
cmake --build build
```

## License

MIT License
