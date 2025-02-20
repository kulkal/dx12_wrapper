/*
Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.

NVIDIA CORPORATION and its licensors retain all intellectual property
and proprietary rights in and to this software, related documentation
and any modifications thereto. Any use, reproduction, disclosure or
distribution of this software and related documentation without an express
license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#pragma once

namespace nri
{
    constexpr std::array<VkIndexType, (uint32_t)IndexType::MAX_NUM> INDEX_TYPE_TABLE = {
        VK_INDEX_TYPE_UINT16,
        VK_INDEX_TYPE_UINT32
    };

    constexpr std::array<VkImageLayout, (uint32_t)nri::TextureLayout::MAX_NUM> LAYOUT_TABLE = {
        VK_IMAGE_LAYOUT_GENERAL,                                        // GENERAL,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,                       // COLOR_ATTACHMENT,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,               // DEPTH_STENCIL,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL,                // DEPTH_STENCIL_READONLY,
        VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR, // DEPTH_READONLY,
        VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR, // STENCIL_READONLY,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,                       // SHADER_RESOURCE,
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,                                // PRESENT,
        VK_IMAGE_LAYOUT_UNDEFINED                                       // UNKNOWN
    };

    constexpr VkBufferUsageFlags GetBufferUsageFlags(BufferUsageBits usageMask, uint32_t structureStride)
    {
        VkBufferUsageFlags flags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT;

        if (usageMask & BufferUsageBits::VERTEX_BUFFER)
            flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

        if (usageMask & BufferUsageBits::INDEX_BUFFER)
            flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;

        if (usageMask & BufferUsageBits::CONSTANT_BUFFER)
            flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;

        if (usageMask & BufferUsageBits::ARGUMENT_BUFFER)
            flags |= VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;

        if (usageMask & BufferUsageBits::RAY_TRACING_BUFFER)
            flags |= VK_BUFFER_USAGE_RAY_TRACING_BIT_NV;

        if (usageMask & BufferUsageBits::SHADER_RESOURCE)
        {
            if (structureStride == 0)
                flags |= VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;
            else
                flags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        }

        if (usageMask & BufferUsageBits::SHADER_RESOURCE_STORAGE)
        {
            if (structureStride == 0)
                flags |= VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT;
            else
                flags |= VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        }

        return flags;
    }

    constexpr VkIndexType GetIndexType(IndexType indexType)
    {
        return INDEX_TYPE_TABLE[(uint32_t)indexType];
    }

    constexpr VkImageLayout GetImageLayout(TextureLayout layout)
    {
        return LAYOUT_TABLE[(uint32_t)layout];
    }

    constexpr VkAccessFlags GetAccessFlags(AccessBits mask)
    {
        VkAccessFlags flags = 0;

        if (mask & AccessBits::VERTEX_BUFFER)
            flags |= VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;

        if (mask & AccessBits::INDEX_BUFFER)
            flags |= VK_ACCESS_INDEX_READ_BIT;

        if (mask & AccessBits::CONSTANT_BUFFER)
            flags |= VK_ACCESS_UNIFORM_READ_BIT;

        if (mask & AccessBits::ARGUMENT_BUFFER)
            flags |= VK_ACCESS_INDIRECT_COMMAND_READ_BIT;

        if (mask & AccessBits::SHADER_RESOURCE)
            flags |= VK_ACCESS_SHADER_READ_BIT;

        if (mask & AccessBits::SHADER_RESOURCE_STORAGE)
            flags |= VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT;

        if (mask & AccessBits::COLOR_ATTACHMENT)
            flags |= VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT; // TODO: add READ bit too?

        if (mask & AccessBits::DEPTH_STENCIL_WRITE)
            flags |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        if (mask & AccessBits::DEPTH_STENCIL_READ)
            flags |= VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;

        if (mask & AccessBits::COPY_SOURCE)
            flags |= VK_ACCESS_TRANSFER_READ_BIT;

        if (mask & AccessBits::COPY_DESTINATION)
            flags |= VK_ACCESS_TRANSFER_WRITE_BIT;

        if (mask & AccessBits::ACCELERATION_STRUCTURE_READ)
            flags |= VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV;

        if (mask & AccessBits::ACCELERATION_STRUCTURE_WRITE)
            flags |= VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV;

        return flags;
    }

    constexpr std::array<VkDescriptorType, (uint32_t)DescriptorType::MAX_NUM> DESCRIPTOR_TYPES =
    {
        VK_DESCRIPTOR_TYPE_SAMPLER,                     // SAMPLER
        VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,              // CONSTANT_BUFFER
        VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,               // TEXTURE
        VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,               // STORAGE_TEXTURE
        VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,        // BUFFER
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,              // STORAGE_BUFFER
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,              // STRUCTURED_BUFFER
        VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,              // STORAGE_STRUCTURED_BUFFER
        VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV,   // ACCELERATION_STRUCTURE
    };

    constexpr VkDescriptorType GetDescriptorType(DescriptorType type)
    {
        return DESCRIPTOR_TYPES[(uint32_t)type];
    }

    constexpr std::array<VkShaderStageFlags, (uint32_t)ShaderStage::MAX_NUM> SHADER_STAGE_TABLE = {
        VK_SHADER_STAGE_ALL,                            // ALL,
        VK_SHADER_STAGE_VERTEX_BIT,                     // VERTEX,
        VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,       // TESS_CONTROL,
        VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,    // TESS_EVALUATION,
        VK_SHADER_STAGE_GEOMETRY_BIT,                   // GEOMETRY,
        VK_SHADER_STAGE_FRAGMENT_BIT,                   // FRAGMENT,
        VK_SHADER_STAGE_COMPUTE_BIT,                    // COMPUTE,
        VK_SHADER_STAGE_RAYGEN_BIT_NV,                  // RAYGEN,
        VK_SHADER_STAGE_MISS_BIT_NV,                    // MISS,
        VK_SHADER_STAGE_INTERSECTION_BIT_NV,            // INTERSECTION,
        VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV,             // CLOSEST_HIT,
        VK_SHADER_STAGE_ANY_HIT_BIT_NV,                 // ANY_HIT
        VK_SHADER_STAGE_CALLABLE_BIT_NV,                // CALLABLE
        VK_SHADER_STAGE_TASK_BIT_NV,                    // MESH_CONTROL
        VK_SHADER_STAGE_MESH_BIT_NV                     // MESH_EVALUATION
    };

    constexpr VkShaderStageFlags GetShaderStageFlags(ShaderStage stage)
    {
        return SHADER_STAGE_TABLE[(uint32_t)stage];
    }

    constexpr std::array<VkFormat, (uint32_t)Format::MAX_NUM> VK_FORMAT = {
        VK_FORMAT_UNDEFINED,        // UNKNOWN

        VK_FORMAT_R8_UNORM,         // R8_UNORM
        VK_FORMAT_R8_SNORM,         // R8_SNORM
        VK_FORMAT_R8_UINT,          // R8_UINT
        VK_FORMAT_R8_SINT,          // R8_SINT

        VK_FORMAT_R8G8_UNORM,       // RG8_UNORM
        VK_FORMAT_R8G8_SNORM,       // RG8_SNORM
        VK_FORMAT_R8G8_UINT,        // RG8_UINT
        VK_FORMAT_R8G8_SINT,        // RG8_SINT

        VK_FORMAT_B8G8R8A8_UNORM,   // BGRA8_UNORM

        VK_FORMAT_R8G8B8A8_UNORM,   // RGBA8_UNORM
        VK_FORMAT_R8G8B8A8_SNORM,   // RGBA8_SNORM
        VK_FORMAT_R8G8B8A8_UINT,    // RGBA8_UINT
        VK_FORMAT_R8G8B8A8_SINT,    // RGBA8_SINT
        VK_FORMAT_R8G8B8A8_SRGB,    // RGBA8_SRGB

        VK_FORMAT_R16_UNORM,        // R16_UNORM
        VK_FORMAT_R16_SNORM,        // R16_SNORM
        VK_FORMAT_R16_UINT,         // R16_UINT
        VK_FORMAT_R16_SINT,         // R16_SINT
        VK_FORMAT_R16_SFLOAT,       // R16_SFLOAT

        VK_FORMAT_R16G16_UNORM,     // RG16_UNORM
        VK_FORMAT_R16G16_SNORM,     // RG16_SNORM
        VK_FORMAT_R16G16_UINT,      // RG16_UINT
        VK_FORMAT_R16G16_SINT,      // RG16_SINT
        VK_FORMAT_R16G16_SFLOAT,    // RG16_SFLOAT

        VK_FORMAT_R16G16B16A16_UNORM,   // RGBA16_UNORM
        VK_FORMAT_R16G16B16A16_SNORM,   // RGBA16_SNORM
        VK_FORMAT_R16G16B16A16_UINT,    // RGBA16_UINT
        VK_FORMAT_R16G16B16A16_SINT,    // RGBA16_SINT
        VK_FORMAT_R16G16B16A16_SFLOAT,  // RGBA16_SFLOAT

        VK_FORMAT_R32_UINT,         // R32_UINT
        VK_FORMAT_R32_SINT,         // R32_SINT
        VK_FORMAT_R32_SFLOAT,       // R32_SFLOAT

        VK_FORMAT_R32G32_UINT,      // RG32_UINT
        VK_FORMAT_R32G32_SINT,      // RG32_SINT
        VK_FORMAT_R32G32_SFLOAT,    // RG32_SFLOAT

        VK_FORMAT_R32G32B32_UINT,   // RGB32_UINT
        VK_FORMAT_R32G32B32_SINT,   // RGB32_SINT
        VK_FORMAT_R32G32B32_SFLOAT, // RGB32_SFLOAT

        VK_FORMAT_R32G32B32A32_UINT,    // RGB32_UINT
        VK_FORMAT_R32G32B32A32_SINT,    // RGB32_SINT
        VK_FORMAT_R32G32B32A32_SFLOAT,  // RGB32_SFLOAT

        VK_FORMAT_A2B10G10R10_UNORM_PACK32,     // R10_G10_B10_A2_UNORM
        VK_FORMAT_A2B10G10R10_UINT_PACK32,      // R10_G10_B10_A2_UINT
        VK_FORMAT_B10G11R11_UFLOAT_PACK32,      // R11_G11_B10_UFLOAT
        VK_FORMAT_E5B9G9R9_UFLOAT_PACK32,       // R9_G9_B9_E5_UFLOAT

        VK_FORMAT_BC1_RGBA_UNORM_BLOCK, // BC1_RGBA_UNORM
        VK_FORMAT_BC1_RGBA_SRGB_BLOCK,  // BC1_RGBA_SRGB
        VK_FORMAT_BC2_UNORM_BLOCK,      // BC2_RGBA_UNORM
        VK_FORMAT_BC2_SRGB_BLOCK,       // BC2_RGBA_SRGB
        VK_FORMAT_BC3_UNORM_BLOCK,      // BC3_RGBA_UNORM
        VK_FORMAT_BC3_SRGB_BLOCK,       // BC3_RGBA_SRGB
        VK_FORMAT_BC4_UNORM_BLOCK,      // BC4_R_UNORM
        VK_FORMAT_BC4_SNORM_BLOCK,      // BC4_R_SNORM
        VK_FORMAT_BC5_UNORM_BLOCK,      // BC5_RG_UNORM
        VK_FORMAT_BC5_SNORM_BLOCK,      // BC5_RG_SNORM
        VK_FORMAT_BC6H_UFLOAT_BLOCK,    // BC6H_RGB_UFLOAT
        VK_FORMAT_BC6H_SFLOAT_BLOCK,    // BC6H_RGB_SFLOAT
        VK_FORMAT_BC7_UNORM_BLOCK,      // BC7_RGBA_UNORM
        VK_FORMAT_BC7_SRGB_BLOCK,       // BC7_RGBA_SRGB

        // Depth-specific

        VK_FORMAT_D16_UNORM,            // D16_UNORM
        VK_FORMAT_D24_UNORM_S8_UINT,    // D24_UNORM_S8_UINT
        VK_FORMAT_D32_SFLOAT,           // D32_SFLOAT
        VK_FORMAT_D32_SFLOAT_S8_UINT,   // D32_SFLOAT_S8_UINT_X24_TYPELESS

        VK_FORMAT_X8_D24_UNORM_PACK32,  // D24_UNORM_X8_TYPELESS
        VK_FORMAT_D24_UNORM_S8_UINT,    // X24_TYPLESS_S8_UINT /// TODO: there is no such format in VK
        VK_FORMAT_D32_SFLOAT_S8_UINT,   // X32_TYPLESS_S8_UINT_X24_TYPELESS
        VK_FORMAT_D32_SFLOAT_S8_UINT    // D32_SFLOAT_X8_TYPLESS_X24_TYPELESS
    };

    constexpr VkFormat GetVkFormat(Format format)
    {
        return VK_FORMAT[(uint32_t)format];
    }

    // TODO: add packed formats and depth-specific
    constexpr std::array<Format, 261> FORMAT = {
        Format::UNKNOWN, // VK_FORMAT_UNDEFINED = 0,
        Format::UNKNOWN, // VK_FORMAT_R4G4_UNORM_PACK8 = 1,
        Format::UNKNOWN, // VK_FORMAT_R4G4B4A4_UNORM_PACK16 = 2,
        Format::UNKNOWN, // VK_FORMAT_B4G4R4A4_UNORM_PACK16 = 3,
        Format::UNKNOWN, // VK_FORMAT_R5G6B5_UNORM_PACK16 = 4,
        Format::UNKNOWN, // VK_FORMAT_B5G6R5_UNORM_PACK16 = 5,
        Format::UNKNOWN, // VK_FORMAT_R5G5B5A1_UNORM_PACK16 = 6,
        Format::UNKNOWN, // VK_FORMAT_B5G5R5A1_UNORM_PACK16 = 7,
        Format::UNKNOWN, // VK_FORMAT_A1R5G5B5_UNORM_PACK16 = 8,
        Format::R8_UNORM, // VK_FORMAT_R8_UNORM = 9,
        Format::R8_SNORM, // VK_FORMAT_R8_SNORM = 10,
        Format::UNKNOWN, // VK_FORMAT_R8_USCALED = 11,
        Format::UNKNOWN, // VK_FORMAT_R8_SSCALED = 12,
        Format::R8_UINT, // VK_FORMAT_R8_UINT = 13,
        Format::R8_SINT, // VK_FORMAT_R8_SINT = 14,
        Format::UNKNOWN, // VK_FORMAT_R8_SRGB = 15,
        Format::RG8_UNORM, // VK_FORMAT_R8G8_UNORM = 16,
        Format::RG8_SNORM, // VK_FORMAT_R8G8_SNORM = 17,
        Format::UNKNOWN, // VK_FORMAT_R8G8_USCALED = 18,
        Format::UNKNOWN, // VK_FORMAT_R8G8_SSCALED = 19,
        Format::RG8_UINT, // VK_FORMAT_R8G8_UINT = 20,
        Format::RG8_SINT, // VK_FORMAT_R8G8_SINT = 21,
        Format::UNKNOWN, // VK_FORMAT_R8G8_SRGB = 22,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_UNORM = 23,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_SNORM = 24,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_USCALED = 25,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_SSCALED = 26,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_UINT = 27,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_SINT = 28,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8_SRGB = 29,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_UNORM = 30,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_SNORM = 31,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_USCALED = 32,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_SSCALED = 33,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_UINT = 34,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_SINT = 35,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8_SRGB = 36,
        Format::RGBA8_UNORM, // VK_FORMAT_R8G8B8A8_UNORM = 37,
        Format::RGBA8_SNORM, // VK_FORMAT_R8G8B8A8_SNORM = 38,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8A8_USCALED = 39,
        Format::UNKNOWN, // VK_FORMAT_R8G8B8A8_SSCALED = 40,
        Format::RGBA8_UINT, // VK_FORMAT_R8G8B8A8_UINT = 41,
        Format::RGBA8_SINT, // VK_FORMAT_R8G8B8A8_SINT = 42,
        Format::RGBA8_SRGB, // VK_FORMAT_R8G8B8A8_SRGB = 43,
        Format::BGRA8_UNORM, // VK_FORMAT_B8G8R8A8_UNORM = 44,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8A8_SNORM = 45,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8A8_USCALED = 46,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8A8_SSCALED = 47,
        Format::RGBA8_UINT, // VK_FORMAT_B8G8R8A8_UINT = 48,
        Format::RGBA8_SINT, // VK_FORMAT_B8G8R8A8_SINT = 49,
        Format::RGBA8_SRGB, // VK_FORMAT_B8G8R8A8_SRGB = 50,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_UNORM_PACK32 = 51,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_SNORM_PACK32 = 52,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_USCALED_PACK32 = 53,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_SSCALED_PACK32 = 54,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_UINT_PACK32 = 55,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_SINT_PACK32 = 56,
        Format::UNKNOWN, // VK_FORMAT_A8B8G8R8_SRGB_PACK32 = 57,
        Format::UNKNOWN, // VK_FORMAT_A2R10G10B10_UNORM_PACK32 = 58,
        Format::UNKNOWN, // VK_FORMAT_A2R10G10B10_SNORM_PACK32 = 59,
        Format::UNKNOWN, // VK_FORMAT_A2R10G10B10_USCALED_PACK32 = 60,
        Format::UNKNOWN, // VK_FORMAT_A2R10G10B10_SSCALED_PACK32 = 61,
        Format::UNKNOWN, // VK_FORMAT_A2R10G10B10_UINT_PACK32 = 62,
        Format::UNKNOWN, // VK_FORMAT_A2R10G10B10_SINT_PACK32 = 63,
        Format::UNKNOWN, // VK_FORMAT_A2B10G10R10_UNORM_PACK32 = 64,
        Format::UNKNOWN, // VK_FORMAT_A2B10G10R10_SNORM_PACK32 = 65,
        Format::UNKNOWN, // VK_FORMAT_A2B10G10R10_USCALED_PACK32 = 66,
        Format::UNKNOWN, // VK_FORMAT_A2B10G10R10_SSCALED_PACK32 = 67,
        Format::UNKNOWN, // VK_FORMAT_A2B10G10R10_UINT_PACK32 = 68,
        Format::UNKNOWN, // VK_FORMAT_A2B10G10R10_SINT_PACK32 = 69,
        Format::R16_UNORM, // VK_FORMAT_R16_UNORM = 70,
        Format::R16_SNORM, // VK_FORMAT_R16_SNORM = 71,
        Format::UNKNOWN, // VK_FORMAT_R16_USCALED = 72,
        Format::UNKNOWN, // VK_FORMAT_R16_SSCALED = 73,
        Format::R16_UINT, // VK_FORMAT_R16_UINT = 74,
        Format::R16_SINT, // VK_FORMAT_R16_SINT = 75,
        Format::R16_SFLOAT, // VK_FORMAT_R16_SFLOAT = 76,
        Format::RG16_UNORM, // VK_FORMAT_R16G16_UNORM = 77,
        Format::RG16_SNORM, // VK_FORMAT_R16G16_SNORM = 78,
        Format::UNKNOWN, // VK_FORMAT_R16G16_USCALED = 79,
        Format::UNKNOWN, // VK_FORMAT_R16G16_SSCALED = 80,
        Format::RG16_UINT, // VK_FORMAT_R16G16_UINT = 81,
        Format::RG16_SINT, // VK_FORMAT_R16G16_SINT = 82,
        Format::RG16_SFLOAT, // VK_FORMAT_R16G16_SFLOAT = 83,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_UNORM = 84,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_SNORM = 85,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_USCALED = 86,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_SSCALED = 87,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_UINT = 88,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_SINT = 89,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16_SFLOAT = 90,
        Format::RGBA16_UNORM, // VK_FORMAT_R16G16B16A16_UNORM = 91,
        Format::RGBA16_SNORM, // VK_FORMAT_R16G16B16A16_SNORM = 92,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16A16_USCALED = 93,
        Format::UNKNOWN, // VK_FORMAT_R16G16B16A16_SSCALED = 94,
        Format::RGBA16_UINT, // VK_FORMAT_R16G16B16A16_UINT = 95,
        Format::RGBA16_SINT, // VK_FORMAT_R16G16B16A16_SINT = 96,
        Format::RGBA16_SFLOAT, // VK_FORMAT_R16G16B16A16_SFLOAT = 97,
        Format::R32_UINT, // VK_FORMAT_R32_UINT = 98,
        Format::R32_SINT, // VK_FORMAT_R32_SINT = 99,
        Format::R32_SFLOAT, // VK_FORMAT_R32_SFLOAT = 100,
        Format::RG32_UINT, // VK_FORMAT_R32G32_UINT = 101,
        Format::RG32_SINT, // VK_FORMAT_R32G32_SINT = 102,
        Format::RG32_SFLOAT, // VK_FORMAT_R32G32_SFLOAT = 103,
        Format::RGB32_UINT, // VK_FORMAT_R32G32B32_UINT = 104,
        Format::RGB32_SINT, // VK_FORMAT_R32G32B32_SINT = 105,
        Format::RGB32_SFLOAT, // VK_FORMAT_R32G32B32_SFLOAT = 106,
        Format::RGBA32_UINT, // VK_FORMAT_R32G32B32A32_UINT = 107,
        Format::RGBA32_SINT, // VK_FORMAT_R32G32B32A32_SINT = 108,
        Format::RGBA32_SFLOAT, // VK_FORMAT_R32G32B32A32_SFLOAT = 109,
        Format::UNKNOWN, // VK_FORMAT_R64_UINT = 110,
        Format::UNKNOWN, // VK_FORMAT_R64_SINT = 111,
        Format::UNKNOWN, // VK_FORMAT_R64_SFLOAT = 112,
        Format::UNKNOWN, // VK_FORMAT_R64G64_UINT = 113,
        Format::UNKNOWN, // VK_FORMAT_R64G64_SINT = 114,
        Format::UNKNOWN, // VK_FORMAT_R64G64_SFLOAT = 115,
        Format::UNKNOWN, // VK_FORMAT_R64G64B64_UINT = 116,
        Format::UNKNOWN, // VK_FORMAT_R64G64B64_SINT = 117,
        Format::UNKNOWN, // VK_FORMAT_R64G64B64_SFLOAT = 118,
        Format::UNKNOWN, // VK_FORMAT_R64G64B64A64_UINT = 119,
        Format::UNKNOWN, // VK_FORMAT_R64G64B64A64_SINT = 120,
        Format::UNKNOWN, // VK_FORMAT_R64G64B64A64_SFLOAT = 121,
        Format::R11_G11_B10_UFLOAT, // VK_FORMAT_B10G11R11_UFLOAT_PACK32 = 122,
        Format::R9_G9_B9_E5_UFLOAT, // VK_FORMAT_E5B9G9R9_UFLOAT_PACK32 = 123,
        Format::UNKNOWN, // VK_FORMAT_D16_UNORM = 124,
        Format::UNKNOWN, // VK_FORMAT_X8_D24_UNORM_PACK32 = 125,
        Format::UNKNOWN, // VK_FORMAT_D32_SFLOAT = 126,
        Format::UNKNOWN, // VK_FORMAT_S8_UINT = 127,
        Format::UNKNOWN, // VK_FORMAT_D16_UNORM_S8_UINT = 128,
        Format::UNKNOWN, // VK_FORMAT_D24_UNORM_S8_UINT = 129,
        Format::UNKNOWN, // VK_FORMAT_D32_SFLOAT_S8_UINT = 130,
        Format::UNKNOWN, // VK_FORMAT_BC1_RGB_UNORM_BLOCK = 131,
        Format::UNKNOWN, // VK_FORMAT_BC1_RGB_SRGB_BLOCK = 132,
        Format::UNKNOWN, // VK_FORMAT_BC1_RGBA_UNORM_BLOCK = 133,
        Format::UNKNOWN, // VK_FORMAT_BC1_RGBA_SRGB_BLOCK = 134,
        Format::UNKNOWN, // VK_FORMAT_BC2_UNORM_BLOCK = 135,
        Format::UNKNOWN, // VK_FORMAT_BC2_SRGB_BLOCK = 136,
        Format::UNKNOWN, // VK_FORMAT_BC3_UNORM_BLOCK = 137,
        Format::UNKNOWN, // VK_FORMAT_BC3_SRGB_BLOCK = 138,
        Format::UNKNOWN, // VK_FORMAT_BC4_UNORM_BLOCK = 139,
        Format::UNKNOWN, // VK_FORMAT_BC4_SNORM_BLOCK = 140,
        Format::UNKNOWN, // VK_FORMAT_BC5_UNORM_BLOCK = 141,
        Format::UNKNOWN, // VK_FORMAT_BC5_SNORM_BLOCK = 142,
        Format::UNKNOWN, // VK_FORMAT_BC6H_UFLOAT_BLOCK = 143,
        Format::UNKNOWN, // VK_FORMAT_BC6H_SFLOAT_BLOCK = 144,
        Format::UNKNOWN, // VK_FORMAT_BC7_UNORM_BLOCK = 145,
        Format::UNKNOWN, // VK_FORMAT_BC7_SRGB_BLOCK = 146,
        Format::UNKNOWN, // VK_FORMAT_ETC2_R8G8B8_UNORM_BLOCK = 147,
        Format::UNKNOWN, // VK_FORMAT_ETC2_R8G8B8_SRGB_BLOCK = 148,
        Format::UNKNOWN, // VK_FORMAT_ETC2_R8G8B8A1_UNORM_BLOCK = 149,
        Format::UNKNOWN, // VK_FORMAT_ETC2_R8G8B8A1_SRGB_BLOCK = 150,
        Format::UNKNOWN, // VK_FORMAT_ETC2_R8G8B8A8_UNORM_BLOCK = 151,
        Format::UNKNOWN, // VK_FORMAT_ETC2_R8G8B8A8_SRGB_BLOCK = 152,
        Format::UNKNOWN, // VK_FORMAT_EAC_R11_UNORM_BLOCK = 153,
        Format::UNKNOWN, // VK_FORMAT_EAC_R11_SNORM_BLOCK = 154,
        Format::UNKNOWN, // VK_FORMAT_EAC_R11G11_UNORM_BLOCK = 155,
        Format::UNKNOWN, // VK_FORMAT_EAC_R11G11_SNORM_BLOCK = 156,
        Format::UNKNOWN, // VK_FORMAT_ASTC_4x4_UNORM_BLOCK = 157,
        Format::UNKNOWN, // VK_FORMAT_ASTC_4x4_SRGB_BLOCK = 158,
        Format::UNKNOWN, // VK_FORMAT_ASTC_5x4_UNORM_BLOCK = 159,
        Format::UNKNOWN, // VK_FORMAT_ASTC_5x4_SRGB_BLOCK = 160,
        Format::UNKNOWN, // VK_FORMAT_ASTC_5x5_UNORM_BLOCK = 161,
        Format::UNKNOWN, // VK_FORMAT_ASTC_5x5_SRGB_BLOCK = 162,
        Format::UNKNOWN, // VK_FORMAT_ASTC_6x5_UNORM_BLOCK = 163,
        Format::UNKNOWN, // VK_FORMAT_ASTC_6x5_SRGB_BLOCK = 164,
        Format::UNKNOWN, // VK_FORMAT_ASTC_6x6_UNORM_BLOCK = 165,
        Format::UNKNOWN, // VK_FORMAT_ASTC_6x6_SRGB_BLOCK = 166,
        Format::UNKNOWN, // VK_FORMAT_ASTC_8x5_UNORM_BLOCK = 167,
        Format::UNKNOWN, // VK_FORMAT_ASTC_8x5_SRGB_BLOCK = 168,
        Format::UNKNOWN, // VK_FORMAT_ASTC_8x6_UNORM_BLOCK = 169,
        Format::UNKNOWN, // VK_FORMAT_ASTC_8x6_SRGB_BLOCK = 170,
        Format::UNKNOWN, // VK_FORMAT_ASTC_8x8_UNORM_BLOCK = 171,
        Format::UNKNOWN, // VK_FORMAT_ASTC_8x8_SRGB_BLOCK = 172,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x5_UNORM_BLOCK = 173,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x5_SRGB_BLOCK = 174,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x6_UNORM_BLOCK = 175,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x6_SRGB_BLOCK = 176,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x8_UNORM_BLOCK = 177,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x8_SRGB_BLOCK = 178,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x10_UNORM_BLOCK = 179,
        Format::UNKNOWN, // VK_FORMAT_ASTC_10x10_SRGB_BLOCK = 180,
        Format::UNKNOWN, // VK_FORMAT_ASTC_12x10_UNORM_BLOCK = 181,
        Format::UNKNOWN, // VK_FORMAT_ASTC_12x10_SRGB_BLOCK = 182,
        Format::UNKNOWN, // VK_FORMAT_ASTC_12x12_UNORM_BLOCK = 183,
        Format::UNKNOWN, // VK_FORMAT_ASTC_12x12_SRGB_BLOCK = 184,
        Format::UNKNOWN, // VK_FORMAT_G8B8G8R8_422_UNORM = 1000156000,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8G8_422_UNORM = 1000156001,
        Format::UNKNOWN, // VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM = 1000156002,
        Format::UNKNOWN, // VK_FORMAT_G8_B8R8_2PLANE_420_UNORM = 1000156003,
        Format::UNKNOWN, // VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM = 1000156004,
        Format::UNKNOWN, // VK_FORMAT_G8_B8R8_2PLANE_422_UNORM = 1000156005,
        Format::UNKNOWN, // VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM = 1000156006,
        Format::UNKNOWN, // VK_FORMAT_R10X6_UNORM_PACK16 = 1000156007,
        Format::UNKNOWN, // VK_FORMAT_R10X6G10X6_UNORM_2PACK16 = 1000156008,
        Format::UNKNOWN, // VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16 = 1000156009,
        Format::UNKNOWN, // VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16 = 1000156010,
        Format::UNKNOWN, // VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16 = 1000156011,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16 = 1000156012,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16 = 1000156013,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16 = 1000156014,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16 = 1000156015,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16 = 1000156016,
        Format::UNKNOWN, // VK_FORMAT_R12X4_UNORM_PACK16 = 1000156017,
        Format::UNKNOWN, // VK_FORMAT_R12X4G12X4_UNORM_2PACK16 = 1000156018,
        Format::UNKNOWN, // VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16 = 1000156019,
        Format::UNKNOWN, // VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16 = 1000156020,
        Format::UNKNOWN, // VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16 = 1000156021,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16 = 1000156022,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16 = 1000156023,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16 = 1000156024,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16 = 1000156025,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16 = 1000156026,
        Format::UNKNOWN, // VK_FORMAT_G16B16G16R16_422_UNORM = 1000156027,
        Format::UNKNOWN, // VK_FORMAT_B16G16R16G16_422_UNORM = 1000156028,
        Format::UNKNOWN, // VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM = 1000156029,
        Format::UNKNOWN, // VK_FORMAT_G16_B16R16_2PLANE_420_UNORM = 1000156030,
        Format::UNKNOWN, // VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM = 1000156031,
        Format::UNKNOWN, // VK_FORMAT_G16_B16R16_2PLANE_422_UNORM = 1000156032,
        Format::UNKNOWN, // VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM = 1000156033,
        Format::UNKNOWN, // VK_FORMAT_PVRTC1_2BPP_UNORM_BLOCK_IMG = 1000054000,
        Format::UNKNOWN, // VK_FORMAT_PVRTC1_4BPP_UNORM_BLOCK_IMG = 1000054001,
        Format::UNKNOWN, // VK_FORMAT_PVRTC2_2BPP_UNORM_BLOCK_IMG = 1000054002,
        Format::UNKNOWN, // VK_FORMAT_PVRTC2_4BPP_UNORM_BLOCK_IMG = 1000054003,
        Format::UNKNOWN, // VK_FORMAT_PVRTC1_2BPP_SRGB_BLOCK_IMG = 1000054004,
        Format::UNKNOWN, // VK_FORMAT_PVRTC1_4BPP_SRGB_BLOCK_IMG = 1000054005,
        Format::UNKNOWN, // VK_FORMAT_PVRTC2_2BPP_SRGB_BLOCK_IMG = 1000054006,
        Format::UNKNOWN, // VK_FORMAT_PVRTC2_4BPP_SRGB_BLOCK_IMG = 1000054007,
        Format::UNKNOWN, // VK_FORMAT_G8B8G8R8_422_UNORM_KHR = VK_FORMAT_G8B8G8R8_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_B8G8R8G8_422_UNORM_KHR = VK_FORMAT_B8G8R8G8_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_420_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G8_B8R8_2PLANE_420_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_420_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G8_B8R8_2PLANE_422_UNORM_KHR = VK_FORMAT_G8_B8R8_2PLANE_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM_KHR = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM,
        Format::UNKNOWN, // VK_FORMAT_R10X6_UNORM_PACK16_KHR = VK_FORMAT_R10X6_UNORM_PACK16,
        Format::UNKNOWN, // VK_FORMAT_R10X6G10X6_UNORM_2PACK16_KHR = VK_FORMAT_R10X6G10X6_UNORM_2PACK16,
        Format::UNKNOWN, // VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16_KHR = VK_FORMAT_R10X6G10X6B10X6A10X6_UNORM_4PACK16,
        Format::UNKNOWN, // VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_G10X6B10X6G10X6R10X6_422_UNORM_4PACK16,
        Format::UNKNOWN, // VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16_KHR = VK_FORMAT_B10X6G10X6R10X6G10X6_422_UNORM_4PACK16,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_420_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_420_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_422_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6R10X6_2PLANE_422_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G10X6_B10X6_R10X6_3PLANE_444_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_R12X4_UNORM_PACK16_KHR = VK_FORMAT_R12X4_UNORM_PACK16,
        Format::UNKNOWN, // VK_FORMAT_R12X4G12X4_UNORM_2PACK16_KHR = VK_FORMAT_R12X4G12X4_UNORM_2PACK16,
        Format::UNKNOWN, // VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16_KHR = VK_FORMAT_R12X4G12X4B12X4A12X4_UNORM_4PACK16,
        Format::UNKNOWN, // VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_G12X4B12X4G12X4R12X4_422_UNORM_4PACK16,
        Format::UNKNOWN, // VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16_KHR = VK_FORMAT_B12X4G12X4R12X4G12X4_422_UNORM_4PACK16,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_420_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_420_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_422_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4R12X4_2PLANE_422_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16_KHR = VK_FORMAT_G12X4_B12X4_R12X4_3PLANE_444_UNORM_3PACK16,
        Format::UNKNOWN, // VK_FORMAT_G16B16G16R16_422_UNORM_KHR = VK_FORMAT_G16B16G16R16_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_B16G16R16G16_422_UNORM_KHR = VK_FORMAT_B16G16R16G16_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_420_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G16_B16R16_2PLANE_420_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_420_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_422_UNORM,
        Format::UNKNOWN, // VK_FORMAT_G16_B16R16_2PLANE_422_UNORM_KHR = VK_FORMAT_G16_B16R16_2PLANE_422_UNORM,
        Format::UNKNOWN  // VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM_KHR = VK_FORMAT_G16_B16_R16_3PLANE_444_UNORM,
    };

    constexpr Format GetNRIFormat(VkFormat format)
    {
        if ((uint32_t)format < FORMAT.size())
            return FORMAT[(uint32_t)format];

        return Format::UNKNOWN;
    }

    constexpr std::array<VkPrimitiveTopology, (uint32_t)Topology::MAX_NUM> TOPOLOGIES = {
        VK_PRIMITIVE_TOPOLOGY_POINT_LIST,                       // POINT_LIST
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST,                        // LINE_LIST
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP,                       // LINE_STRIP
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,                    // TRIANGLE_LIST
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,                   // TRIANGLE_STRIP
        VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,         // LINE_LIST_WITH_ADJACENCY
        VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,        // LINE_STRIP_WITH_ADJACENCY
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,     // TRIANGLE_LIST_WITH_ADJACENCY
        VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,    // TRIANGLE_STRIP_WITH_ADJACENCY
        VK_PRIMITIVE_TOPOLOGY_PATCH_LIST                        // PATCH_LIST
    };

    constexpr VkPrimitiveTopology GetTopology(Topology topology)
    {
        return TOPOLOGIES[(uint32_t)topology];
    }

    constexpr std::array<VkCullModeFlags, (uint32_t)CullMode::MAX_NUM> CULL_MODES = {
        VK_CULL_MODE_NONE,      // NONE
        VK_CULL_MODE_FRONT_BIT, // FRONT
        VK_CULL_MODE_BACK_BIT   // BACK
    };

    constexpr VkCullModeFlags GetCullMode(CullMode cullMode)
    {
        return CULL_MODES[(uint32_t)cullMode];
    }

    constexpr std::array<VkPolygonMode, (uint32_t)FillMode::MAX_NUM> POLYGON_MODES = {
        VK_POLYGON_MODE_FILL,   // SOLID
        VK_POLYGON_MODE_LINE,   // WIREFRAME
    };

    constexpr VkPolygonMode GetPolygonMode(FillMode fillMode)
    {
        return POLYGON_MODES[(uint32_t)fillMode];
    }

    constexpr float GetDepthOffset(int32_t)
    {
        return 0.0f; // TODO: implement correct conversion
    }

    constexpr VkSampleCountFlagBits GetSampleCount(uint32_t sampleNum)
    {
        return (VkSampleCountFlagBits)sampleNum;
    }

    constexpr std::array<VkCompareOp, (uint32_t)CompareFunc::MAX_NUM> COMPARE_OP = {
        VK_COMPARE_OP_NEVER,            // NONE
        VK_COMPARE_OP_ALWAYS,           // ALWAYS
        VK_COMPARE_OP_NEVER,            // NEVER
        VK_COMPARE_OP_LESS,             // LESS
        VK_COMPARE_OP_LESS_OR_EQUAL,    // LESS_EQUAL
        VK_COMPARE_OP_EQUAL,            // EQUAL
        VK_COMPARE_OP_GREATER_OR_EQUAL, // GREATER_EQUAL
        VK_COMPARE_OP_GREATER,          // GREATER
        VK_COMPARE_OP_NOT_EQUAL,        // NOT_EQUAL
    };

    constexpr VkCompareOp GetCompareOp(CompareFunc compareFunc)
    {
        return COMPARE_OP[(uint32_t)compareFunc];
    }

    constexpr std::array<VkStencilOp, (uint32_t)StencilFunc::MAX_NUM> STENCIL_OP = {
        VK_STENCIL_OP_KEEP,                     // KEEP,
        VK_STENCIL_OP_ZERO,                     // ZERO,
        VK_STENCIL_OP_REPLACE,                  // REPLACE,
        VK_STENCIL_OP_INCREMENT_AND_CLAMP,      // INCREMENT_AND_CLAMP,
        VK_STENCIL_OP_DECREMENT_AND_CLAMP,      // DECREMENT_AND_CLAMP,
        VK_STENCIL_OP_INVERT,                   // INVERT,
        VK_STENCIL_OP_INCREMENT_AND_WRAP,       // INCREMENT_AND_WRAP,
        VK_STENCIL_OP_DECREMENT_AND_WRAP        // DECREMENT_AND_WRAP
    };

    constexpr VkStencilOp GetStencilOp(StencilFunc stencilFunc)
    {
        return STENCIL_OP[(uint32_t)stencilFunc];
    }

    constexpr std::array<VkLogicOp, (uint32_t)LogicFunc::MAX_NUM> LOGIC_OP = {
        VK_LOGIC_OP_MAX_ENUM,       // NONE
        VK_LOGIC_OP_CLEAR,          // CLEAR
        VK_LOGIC_OP_AND,            // AND
        VK_LOGIC_OP_AND_REVERSE,    // AND_REVERSE
        VK_LOGIC_OP_COPY,           // COPY
        VK_LOGIC_OP_AND_INVERTED,   // AND_INVERTED
        VK_LOGIC_OP_XOR,            // XOR
        VK_LOGIC_OP_OR,             // OR
        VK_LOGIC_OP_NOR,            // NOR
        VK_LOGIC_OP_EQUIVALENT,     // EQUIVALENT
        VK_LOGIC_OP_INVERT,         // INVERT
        VK_LOGIC_OP_OR_REVERSE,     // OR_REVERSE
        VK_LOGIC_OP_COPY_INVERTED,  // COPY_INVERTED
        VK_LOGIC_OP_OR_INVERTED,    // OR_INVERTED
        VK_LOGIC_OP_NAND,           // NAND
        VK_LOGIC_OP_SET             // SET
    };

    constexpr VkLogicOp GetLogicOp(LogicFunc logicFunc)
    {
        return LOGIC_OP[(uint32_t)logicFunc];
    }

    constexpr std::array<VkBlendFactor, (uint32_t)BlendFactor::MAX_NUM> BLEND_FACTOR = {
        VK_BLEND_FACTOR_ZERO,                       // ZERO
        VK_BLEND_FACTOR_ONE,                        // ONE
        VK_BLEND_FACTOR_SRC_COLOR,                  // SRC_COLOR
        VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR,        // ONE_MINUS_SRC_COLOR
        VK_BLEND_FACTOR_DST_COLOR,                  // DST_COLOR
        VK_BLEND_FACTOR_ONE_MINUS_DST_COLOR,        // ONE_MINUS_DST_COLOR
        VK_BLEND_FACTOR_SRC_ALPHA,                  // SRC_ALPHA
        VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,        // ONE_MINUS_SRC_ALPHA
        VK_BLEND_FACTOR_DST_ALPHA,                  // DST_ALPHA
        VK_BLEND_FACTOR_ONE_MINUS_DST_ALPHA,        // ONE_MINUS_DST_ALPHA
        VK_BLEND_FACTOR_CONSTANT_COLOR,             // CONSTANT_COLOR
        VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_COLOR,   // ONE_MINUS_CONSTANT_COLOR
        VK_BLEND_FACTOR_CONSTANT_ALPHA,             // CONSTANT_ALPHA
        VK_BLEND_FACTOR_ONE_MINUS_CONSTANT_ALPHA,   // ONE_MINUS_CONSTANT_ALPHA
        VK_BLEND_FACTOR_SRC_ALPHA_SATURATE,         // SRC_ALPHA_SATURATE
        VK_BLEND_FACTOR_SRC1_COLOR,                 // SRC1_COLOR
        VK_BLEND_FACTOR_ONE_MINUS_SRC1_COLOR,       // ONE_MINUS_SRC1_COLOR
        VK_BLEND_FACTOR_SRC1_ALPHA,                 // SRC1_ALPHA
        VK_BLEND_FACTOR_ONE_MINUS_SRC1_ALPHA,       // ONE_MINUS_SRC1_ALPHA
    };

    constexpr VkBlendFactor GetBlendFactor(BlendFactor blendFactor)
    {
        return BLEND_FACTOR[(uint32_t)blendFactor];
    }

    constexpr std::array<VkBlendOp, (uint32_t)BlendFunc::MAX_NUM> BLEND_OP = {
        VK_BLEND_OP_ADD,                // ADD
        VK_BLEND_OP_SUBTRACT,           // SUBTRACT
        VK_BLEND_OP_REVERSE_SUBTRACT,   // REVERSE_SUBTRACT
        VK_BLEND_OP_MIN,                // MIN
        VK_BLEND_OP_MAX                 // MAX
    };

    constexpr VkBlendOp GetBlendOp(BlendFunc blendFunc)
    {
        return BLEND_OP[(uint32_t)blendFunc];
    }

    constexpr VkColorComponentFlags GetColorComponent(ColorWriteBits colorWriteMask)
    {
        return VkColorComponentFlags(colorWriteMask & ColorWriteBits::RGBA);
    }

    constexpr std::array<VkImageType, (uint32_t)TextureType::MAX_NUM> IMAGE_TYPES = {
        VK_IMAGE_TYPE_1D,
        VK_IMAGE_TYPE_2D,
        VK_IMAGE_TYPE_3D
    };

    constexpr VkImageType GetImageType(TextureType type)
    {
        return IMAGE_TYPES[(uint32_t)type];
    }

    constexpr VkImageUsageFlags GetImageUsageFlags(TextureUsageBits usageMask)
    {
        VkImageUsageFlags flags = VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        if (usageMask & TextureUsageBits::SHADER_RESOURCE)
            flags |= VK_IMAGE_USAGE_SAMPLED_BIT;

        if (usageMask & TextureUsageBits::SHADER_RESOURCE_STORAGE)
            flags |= VK_IMAGE_USAGE_STORAGE_BIT;

        if (usageMask & TextureUsageBits::COLOR_ATTACHMENT)
            flags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        if (usageMask & TextureUsageBits::DEPTH_STENCIL_ATTACHMENT)
            flags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

        return flags;
    }

    constexpr VkImageAspectFlags GetImageAspectFlags(Format format)
    {
        VkImageAspectFlags flags = VK_IMAGE_ASPECT_COLOR_BIT;

        switch (format)
        {
        case Format::D16_UNORM:
        case Format::D32_SFLOAT:
        case Format::R24_UNORM_X8:
        case Format::R32_SFLOAT_X8_X24:
            flags = VK_IMAGE_ASPECT_DEPTH_BIT;
            break;

        case Format::D24_UNORM_S8_UINT:
        case Format::D32_SFLOAT_S8_UINT_X24:
            flags = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
            break;

        case Format::X32_R8_UINT_X24:
        case Format::X24_R8_UINT:
            flags = VK_IMAGE_ASPECT_STENCIL_BIT;
            break;
        }

        return flags;
    }

    constexpr std::array<VkFilter, (uint32_t)Filter::MAX_NUM> FILTER = {
        VK_FILTER_NEAREST,  // NEAREST
        VK_FILTER_LINEAR,   // LINEAR
    };

    constexpr VkFilter GetFilter(Filter filter)
    {
        return FILTER[(uint32_t)filter];
    }

    constexpr std::array<VkSamplerMipmapMode, (uint32_t)Filter::MAX_NUM> SAMPLER_MIPMAP_MODE = {
        VK_SAMPLER_MIPMAP_MODE_NEAREST,  // NEAREST
        VK_SAMPLER_MIPMAP_MODE_LINEAR,   // LINEAR
    };

    constexpr VkSamplerMipmapMode GetSamplerMipmapMode(Filter filter)
    {
        return SAMPLER_MIPMAP_MODE[(uint32_t)filter];
    }

    constexpr std::array<VkSamplerAddressMode, (uint32_t)AddressMode::MAX_NUM> SAMPLER_ADDRESS_MODE = {
        VK_SAMPLER_ADDRESS_MODE_REPEAT,                 // REPEAT
        VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,        // MIRRORED_REPEAT
        VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,          // CLAMP_TO_EDGE
        VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER         // CLAMP_TO_BORDER
    };

    constexpr VkSamplerAddressMode GetSamplerAddressMode(AddressMode addressMode)
    {
        return SAMPLER_ADDRESS_MODE[(uint32_t)addressMode];
    }

    constexpr std::array<VkQueryType, (uint32_t)QueryType::MAX_NUM> QUERY_TYPE = {
        VK_QUERY_TYPE_TIMESTAMP,            // TIMESTAMP
        VK_QUERY_TYPE_OCCLUSION,            // OCCLUSION
        VK_QUERY_TYPE_PIPELINE_STATISTICS   // PIPELINE_STATISTICS
    };

    constexpr VkQueryType GetQueryType(QueryType queryType)
    {
        return QUERY_TYPE[(uint32_t)queryType];
    }

    constexpr VkQueryPipelineStatisticFlags GetQueryPipelineStatisticsFlags(PipelineStatsBits pipelineStatsMask)
    {
        VkQueryPipelineStatisticFlags flags = 0;

        if (pipelineStatsMask & PipelineStatsBits::INPUT_ASSEMBLY_VERTICES)
            flags |= VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT;

        if (pipelineStatsMask & PipelineStatsBits::INPUT_ASSEMBLY_PRIMITIVES)
            flags |= VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT;

        if (pipelineStatsMask & PipelineStatsBits::VERTEX_SHADER_INVOCATIONS)
            flags |= VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT;

        if (pipelineStatsMask & PipelineStatsBits::GEOMETRY_SHADER_INVOCATIONS)
            flags |= VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT;

        if (pipelineStatsMask & PipelineStatsBits::GEOMETRY_SHADER_PRIMITIVES)
            flags |= VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT;

        if (pipelineStatsMask & PipelineStatsBits::CLIPPING_INVOCATIONS)
            flags |= VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT;

        if (pipelineStatsMask & PipelineStatsBits::FRAGMENT_SHADER_INVOCATIONS)
            flags |= VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT;

        if (pipelineStatsMask & PipelineStatsBits::TESS_CONTROL_SHADER_PATCHES)
            flags |= VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT;

        if (pipelineStatsMask & PipelineStatsBits::TESS_EVALUATION_SHADER_INVOCATIONS)
            flags |= VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT;

        if (pipelineStatsMask & PipelineStatsBits::COMPUTE_SHADER_INVOCATIONS)
            flags |= VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT;

        return flags;
    }

    constexpr std::array<VkImageViewType, (uint32_t)Texture1DViewType::MAX_NUM> IMAGE_VIEW_TYPE_1D = {
        VK_IMAGE_VIEW_TYPE_1D,          // SHADER_RESOURCE_1D,
        VK_IMAGE_VIEW_TYPE_1D_ARRAY,    // SHADER_RESOURCE_1D_ARRAY,
        VK_IMAGE_VIEW_TYPE_1D,          // SHADER_RESOURCE_STORAGE_1D,
        VK_IMAGE_VIEW_TYPE_1D_ARRAY,    // SHADER_RESOURCE_STORAGE_1D_ARRAY,
        VK_IMAGE_VIEW_TYPE_1D,          // COLOR_ATTACHMENT,
        VK_IMAGE_VIEW_TYPE_1D,          // DEPTH_STENCIL_ATTACHMENT
    };

    constexpr std::array<VkImageViewType, (uint32_t)Texture2DViewType::MAX_NUM> IMAGE_VIEW_TYPE_2D = {
        VK_IMAGE_VIEW_TYPE_2D,          // SHADER_RESOURCE_2D,
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,    // SHADER_RESOURCE_2D_ARRAY,
        VK_IMAGE_VIEW_TYPE_CUBE,        // SHADER_RESOURCE_CUBE,
        VK_IMAGE_VIEW_TYPE_CUBE_ARRAY,  // SHADER_RESOURCE_CUBE_ARRAY,
        VK_IMAGE_VIEW_TYPE_2D,          // SHADER_RESOURCE_STORAGE_2D,
        VK_IMAGE_VIEW_TYPE_2D_ARRAY,    // SHADER_RESOURCE_STORAGE_2D_ARRAY,
        VK_IMAGE_VIEW_TYPE_2D,          // COLOR_ATTACHMENT,
        VK_IMAGE_VIEW_TYPE_2D,          // DEPTH_STENCIL_ATTACHMENT
    };

    constexpr std::array<VkImageViewType, (uint32_t)Texture3DViewType::MAX_NUM> IMAGE_VIEW_TYPE_3D = {
        VK_IMAGE_VIEW_TYPE_3D, // SHADER_RESOURCE_3D,
        VK_IMAGE_VIEW_TYPE_3D, // SHADER_RESOURCE_STORAGE_3D,
        VK_IMAGE_VIEW_TYPE_3D, // COLOR_ATTACHMENT
    };

    constexpr VkImageViewType GetImageViewType(Texture1DViewType type)
    {
        return IMAGE_VIEW_TYPE_1D[(uint32_t)type];
    }

    constexpr VkImageViewType GetImageViewType(Texture2DViewType type)
    {
        return IMAGE_VIEW_TYPE_2D[(uint32_t)type];
    }

    constexpr VkImageViewType GetImageViewType(Texture3DViewType type)
    {
        return IMAGE_VIEW_TYPE_3D[(uint32_t)type];
    }

    constexpr std::array<VkImageLayout, (uint32_t)Texture1DViewType::MAX_NUM> IMAGE_LAYOUT_1D = {
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_1D,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_1D_ARRAY,
        VK_IMAGE_LAYOUT_GENERAL,                            // SHADER_RESOURCE_STORAGE_1D,
        VK_IMAGE_LAYOUT_GENERAL,                            // SHADER_RESOURCE_STORAGE_1D_ARRAY,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,           // COLOR_ATTACHMENT,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,   // DEPTH_STENCIL_ATTACHMENT
    };

    constexpr std::array<VkImageLayout, (uint32_t)Texture2DViewType::MAX_NUM> IMAGE_LAYOUT_2D = {
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_2D,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_2D_ARRAY,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_CUBE,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_CUBE_ARRAY,
        VK_IMAGE_LAYOUT_GENERAL,                            // SHADER_RESOURCE_STORAGE_2D,
        VK_IMAGE_LAYOUT_GENERAL,                            // SHADER_RESOURCE_STORAGE_2D_ARRAY,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,           // COLOR_ATTACHMENT,
        VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,   // DEPTH_STENCIL_ATTACHMENT
    };

    constexpr std::array<VkImageLayout, (uint32_t)Texture3DViewType::MAX_NUM> IMAGE_LAYOUT_3D = {
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,           // SHADER_RESOURCE_3D,
        VK_IMAGE_LAYOUT_GENERAL,                            // SHADER_RESOURCE_STORAGE_3D,
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,           // COLOR_ATTACHMENT
    };

    constexpr VkImageLayout GetImageLayoutForView(Texture1DViewType type)
    {
        return IMAGE_LAYOUT_1D[(uint32_t)type];
    }

    constexpr VkImageLayout GetImageLayoutForView(Texture2DViewType type)
    {
        return IMAGE_LAYOUT_2D[(uint32_t)type];
    }

    constexpr VkImageLayout GetImageLayoutForView(Texture3DViewType type)
    {
        return IMAGE_LAYOUT_3D[(uint32_t)type];
    }

    constexpr VkAccelerationStructureTypeNV GetAccelerationStructureType(AccelerationStructureType type)
    {
        static_assert( VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV == (uint32_t)AccelerationStructureType::TOP_LEVEL, "Enum mismatch." );
        static_assert( VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV == (uint32_t)AccelerationStructureType::BOTTOM_LEVEL, "Enum mismatch." );
        return (VkAccelerationStructureTypeNV)type;
    }

    constexpr VkBuildAccelerationStructureFlagsNV GetAccelerationStructureBuildFlags(AccelerationStructureBuildBits flags)
    {
        static_assert( VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV == (uint32_t)AccelerationStructureBuildBits::ALLOW_UPDATE, "Enum mismatch." );
        static_assert( VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV == (uint32_t)AccelerationStructureBuildBits::ALLOW_COMPACTION, "Enum mismatch." );
        static_assert( VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV == (uint32_t)AccelerationStructureBuildBits::PREFER_FAST_TRACE, "Enum mismatch." );
        static_assert( VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV == (uint32_t)AccelerationStructureBuildBits::PREFER_FAST_BUILD, "Enum mismatch." );
        static_assert( VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV == (uint32_t)AccelerationStructureBuildBits::MINIMIZE_MEMORY, "Enum mismatch." );
        return (VkBuildAccelerationStructureFlagsNV)flags;
    }

    constexpr VkGeometryFlagsNV GetGeometryFlags(BottomLevelGeometryBits geometryFlags)
    {
        static_assert( VK_GEOMETRY_OPAQUE_BIT_NV == (uint32_t)BottomLevelGeometryBits::OPAQUE_GEOMETRY, "Enum mismatch." );
        static_assert( VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV == (uint32_t)BottomLevelGeometryBits::NO_DUPLICATE_ANY_HIT_INVOCATION, "Enum mismatch." );
        return (VkGeometryFlagsNV)geometryFlags;
    }

    constexpr VkGeometryTypeNV GetGeometryType(GeometryType geometryType)
    {
        static_assert( VK_GEOMETRY_TYPE_TRIANGLES_NV == (uint32_t)GeometryType::TRIANGLES, "Enum mismatch." );
        static_assert( VK_GEOMETRY_TYPE_AABBS_NV == (uint32_t)GeometryType::AABBS, "Enum mismatch." );
        return (VkGeometryTypeNV)geometryType;
    }

    constexpr VkCopyAccelerationStructureModeNV GetCopyMode(CopyMode copyMode)
    {
        static_assert( VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV == (uint32_t)CopyMode::CLONE, "Enum mismatch." );
        static_assert( VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV == (uint32_t)CopyMode::COMPACT, "Enum mismatch." );
        return (VkCopyAccelerationStructureModeNV)copyMode;
    }

    constexpr void ConvertGeometryObjectSizesVK(VkGeometryNV* destObjects, const GeometryObject* sourceObjects, uint32_t objectNum)
    {
        for (uint32_t i = 0; i < objectNum; i++)
        {
            const GeometryObject& geometrySrc = sourceObjects[i];
            VkGeometryNV& geometryDst = destObjects[i];

            geometryDst.sType = VK_STRUCTURE_TYPE_GEOMETRY_NV;
            geometryDst.pNext = nullptr;
            geometryDst.flags = GetGeometryFlags(geometrySrc.flags);
            geometryDst.geometryType = GetGeometryType(geometrySrc.type);
            geometryDst.geometry.aabbs.sType = VK_STRUCTURE_TYPE_GEOMETRY_AABB_NV;
            geometryDst.geometry.aabbs.pNext = nullptr;
            geometryDst.geometry.aabbs.aabbData = VK_NULL_HANDLE;
            geometryDst.geometry.aabbs.numAABBs = geometrySrc.boxes.boxNum;
            geometryDst.geometry.aabbs.stride = 0;
            geometryDst.geometry.aabbs.offset = 0;
            geometryDst.geometry.triangles.sType = VK_STRUCTURE_TYPE_GEOMETRY_TRIANGLES_NV;
            geometryDst.geometry.triangles.pNext = nullptr;
            geometryDst.geometry.triangles.vertexData = VK_NULL_HANDLE;
            geometryDst.geometry.triangles.vertexOffset = 0;
            geometryDst.geometry.triangles.vertexCount = geometrySrc.triangles.vertexNum;
            geometryDst.geometry.triangles.vertexStride = 0;
            geometryDst.geometry.triangles.vertexFormat = GetVkFormat(geometrySrc.triangles.vertexFormat);
            geometryDst.geometry.triangles.indexData = VK_NULL_HANDLE;
            geometryDst.geometry.triangles.indexOffset = 0;
            geometryDst.geometry.triangles.indexCount = geometrySrc.triangles.indexNum;
            geometryDst.geometry.triangles.indexType = GetIndexType(geometrySrc.triangles.indexType);
            geometryDst.geometry.triangles.transformData = VK_NULL_HANDLE;
            geometryDst.geometry.triangles.transformOffset = 0;
        }
    }

    void ConvertGeometryObjectsVK(VkGeometryNV* destObjects, const GeometryObject* sourceObjects, uint32_t objectNum, uint32_t physicalDeviceIndex);

    constexpr std::array<TextureType, (uint32_t)TextureType::MAX_NUM> TEXTURE_TYPE_TABLE = {
        TextureType::TEXTURE_1D, // VK_IMAGE_TYPE_1D
        TextureType::TEXTURE_2D, // VK_IMAGE_TYPE_2D
        TextureType::TEXTURE_3D, // VK_IMAGE_TYPE_3D
    };

    constexpr TextureType GetTextureType(VkImageType type)
    {
        if (type < TEXTURE_TYPE_TABLE.size())
            return TEXTURE_TYPE_TABLE[(uint32_t)type];

        return TextureType::MAX_NUM;
    }

    constexpr Result GetReturnCode(VkResult result)
    {
        switch (result)
        {
        case VK_SUCCESS:
        case VK_EVENT_SET:
        case VK_EVENT_RESET:
            return Result::SUCCESS;

        case VK_ERROR_DEVICE_LOST:
            return Result::DEVICE_LOST;

        case VK_ERROR_SURFACE_LOST_KHR:
        case VK_ERROR_OUT_OF_DATE_KHR:
            return Result::SWAPCHAIN_RESIZE;

        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:
        case VK_ERROR_FORMAT_NOT_SUPPORTED:
        case VK_ERROR_INCOMPATIBLE_DRIVER:
        case VK_ERROR_FEATURE_NOT_PRESENT:
        case VK_ERROR_EXTENSION_NOT_PRESENT:
        case VK_ERROR_LAYER_NOT_PRESENT:
            return Result::UNSUPPORTED;

        case VK_ERROR_INVALID_EXTERNAL_HANDLE:
        case VK_ERROR_VALIDATION_FAILED_EXT:
        case VK_ERROR_INVALID_SHADER_NV:
        case VK_ERROR_NOT_PERMITTED_EXT:
        case VK_SUBOPTIMAL_KHR:
        case VK_ERROR_TOO_MANY_OBJECTS:
        case VK_ERROR_MEMORY_MAP_FAILED:
        case VK_ERROR_INITIALIZATION_FAILED:
        case VK_INCOMPLETE:
        case VK_TIMEOUT:
        case VK_NOT_READY:
            return Result::FAILURE;

        case VK_ERROR_OUT_OF_HOST_MEMORY:
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:
        case VK_ERROR_OUT_OF_POOL_MEMORY:
        case VK_ERROR_FRAGMENTATION_EXT:
        case VK_ERROR_FRAGMENTED_POOL:
            return Result::OUT_OF_MEMORY;
        }
        return Result::FAILURE;
    }
}