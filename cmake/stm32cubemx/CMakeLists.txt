cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# STM32CubeMX generated symbols (macros)
set(MX_Defines_Syms 
	USE_FULL_LL_DRIVER 
	USE_PWR_LDO_SUPPLY 
	USE_HAL_DRIVER 
	STM32H743xx
    $<$<CONFIG:Debug>:DEBUG>
)

# STM32CubeMX generated include paths
set(MX_Include_Dirs
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Composite
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Inc/Legacy
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32H7xx/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/MSC/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_KEYBOARD/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_CUSTOM/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Core/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Target
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/PRINTER/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_MOUSE/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/AUDIO_MIC/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/AUDIO_COMMON
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/COMPOSITE/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/AUDIO_SPKR/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_ACM/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/VIDEO/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_RNDIS/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_ECM/Inc
)

# STM32CubeMX generated application sources
set(MX_Application_Src
    ${CMAKE_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_SOURCE_DIR}/Core/Src/gpio.c
    ${CMAKE_SOURCE_DIR}/Core/Src/memorymap.c
    ${CMAKE_SOURCE_DIR}/Core/Src/usart.c
    ${CMAKE_SOURCE_DIR}/Core/Src/usb_otg.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_it.c
    ${CMAKE_SOURCE_DIR}/Core/Src/stm32h7xx_hal_msp.c
    ${CMAKE_SOURCE_DIR}/Core/Src/sysmem.c
    ${CMAKE_SOURCE_DIR}/Core/Src/syscalls.c
    ${CMAKE_SOURCE_DIR}/startup_stm32h743xx.s
)

# STM32 HAL/LL Drivers
set(STM32_Drivers_Src
    ${CMAKE_SOURCE_DIR}/Core/Src/system_stm32h7xx.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_exti.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_gpio.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_rcc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_utils.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usart.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_dma.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c
    ${CMAKE_SOURCE_DIR}/Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c
)

# Drivers Midllewares


set(Composite_Src
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_ECM/Src/usbd_cdc_ecm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_cdc_ecm_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_RNDIS/Src/usbd_cdc_rndis.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_cdc_rndis_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/VIDEO/Src/usbd_video.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_video_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/CDC_ACM/Src/usbd_cdc_acm.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_cdc_acm_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/AUDIO_SPKR/Src/usbd_audio_spkr.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_audio_spkr_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/COMPOSITE/Src/usbd_composite.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/AUDIO_MIC/Src/usbd_audio_mic.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_audio_mic_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_MOUSE/Src/usbd_hid_mouse.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/PRINTER/Src/usbd_printer.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_printer_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/DFU/Src/usbd_dfu.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_dfu_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Core/Src/usbd_core.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Core/Src/usbd_ctlreq.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Core/Src/usbd_ioreq.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usb_device.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_desc.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Target/usbd_conf.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_CUSTOM/Src/usbd_hid_custom.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_hid_custom_if.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/HID_KEYBOARD/Src/usbd_hid_keyboard.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/MSC/Src/usbd_msc.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/MSC/Src/usbd_msc_bot.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/MSC/Src/usbd_msc_data.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/Class/MSC/Src/usbd_msc_scsi.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/AL94_USB_Composite/COMPOSITE/App/usbd_msc_if.c
)

# Link directories setup
set(MX_LINK_DIRS

)
# Project static libraries
set(MX_LINK_LIBS 
    STM32_Drivers
    Composite	
)
# Interface library for includes and symbols
add_library(stm32cubemx INTERFACE)
target_include_directories(stm32cubemx INTERFACE ${MX_Include_Dirs})
target_compile_definitions(stm32cubemx INTERFACE ${MX_Defines_Syms})

# Create STM32_Drivers static library
add_library(STM32_Drivers OBJECT)
target_sources(STM32_Drivers PRIVATE ${STM32_Drivers_Src})
target_link_libraries(STM32_Drivers PUBLIC stm32cubemx)


# Create Composite static library
add_library(Composite OBJECT)
target_sources(Composite PRIVATE ${Composite_Src})
target_link_libraries(Composite PUBLIC stm32cubemx)

# Add STM32CubeMX generated application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
