# PlatformIO Test Architecture

This project uses PlatformIO + Unity with a layered test architecture.

## Structure
- `test/test_unit_*`: one unit test suite per module
- `test/test_component_*`: component tests across several modules
- `test/test_integration_*`: integration tests for system-level logic
- `test/mocks`: HAL/framework stubs and fakes
- `test/fixtures`: deterministic setup/reset data for tests
- `test/templates`: reusable file templates
- `test/support`: shared notes and helper headers

## Recommended workflow
1. Start with unit tests in `test_unit_<module>`.
2. Mock dependencies from `test/mocks`.
3. Add component tests for cross-module behavior.
4. Add integration tests for startup/sequencing/diagnostics.

## Run tests
- Native logic tests:
  `pio test -e native`
- Unit tests only:
  `pio test -e native -f test_unit_*`
- Component tests only:
  `pio test -e native -f test_component_*`
- Integration tests only:
  `pio test -e native -f test_integration_*`
- Embedded tests (STM32):
  `pio test -e nucleo_g474re`
