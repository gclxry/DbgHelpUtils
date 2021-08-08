﻿#include "common_symbol_names.h"

using namespace std::string_literals;

namespace dlg_help_utils::common_symbol_names
{
    std::wstring const peb_structure_symbol_name = L"ntdll!_PEB"s;
    std::wstring const peb_ldr_structure_symbol_name = L"ntdll!_PEB_LDR_DATA"s;
    std::wstring const rtl_user_process_parameters_structure_symbol_name = L"ntdll!_RTL_USER_PROCESS_PARAMETERS"s;
    std::wstring const teb_structure_symbol_name = L"ntdll!_TEB"s;
    std::wstring const heap_structure_symbol_name = L"ntdll!_HEAP"s;
    std::wstring const heap_segment_structure_symbol_name = L"ntdll!_HEAP_SEGMENT"s;
    std::wstring const heap_entry_structure_symbol_name = L"ntdll!_HEAP_ENTRY"s;
    std::wstring const heap_free_entry_structure_symbol_name = L"ntdll!_HEAP_FREE_ENTRY"s;
    std::wstring const heap_ucr_descriptor_structure_symbol_name = L"ntdll!_HEAP_UCR_DESCRIPTOR"s;
    std::wstring const heap_virtual_alloc_entry_structure_symbol_name = L"ntdll!_HEAP_VIRTUAL_ALLOC_ENTRY"s;
    std::wstring const list_entry_structure_symbol_name = L"ntdll!_LIST_ENTRY"s;
    std::wstring const lfh_heap_structure_symbol_name = L"ntdll!_LFH_HEAP"s;
    std::wstring const lfh_block_zone_structure_symbol_name = L"ntdll!_LFH_BLOCK_ZONE"s;
    std::wstring const heap_subsegment_structure_symbol_name = L"ntdll!_HEAP_SUBSEGMENT"s;
    std::wstring const heap_user_data_header_structure_symbol_name = L"ntdll!_HEAP_USERDATA_HEADER"s;
    std::wstring const heap_user_data_offsets_structure_symbol_name = L"ntdll!_HEAP_USERDATA_OFFSETS"s;

    // ReSharper disable once IdentifierTypo
    std::wstring const rtlp_lfh_key_global_symbol_name = L"ntdll!RtlpLFHKey"s;

    std::wstring const peb_structure_ldr_field_symbol_name = L"ldr"s;
    std::wstring const peb_structure_process_parameters_field_symbol_name = L"ProcessParameters"s;
    std::wstring const peb_structure_nt_global_flag_field_symbol_name = L"NtGlobalFlag"s;
    std::wstring const peb_structure_process_heap_field_symbol_name = L"ProcessHeap"s;
    std::wstring const peb_structure_number_of_heaps_field_symbol_name = L"NumberOfHeaps"s;
    std::wstring const peb_structure_process_heaps_field_symbol_name = L"ProcessHeaps"s;
    std::wstring const rtl_user_process_parameters_structure_environment_field_symbol_name = L"Environment"s;
    std::wstring const teb_structure_process_environment_block_field_symbol_name = L"ProcessEnvironmentBlock"s;
    std::wstring const heap_segment_signature_field_symbol_name = L"Segment.SegmentSignature"s;
    std::wstring const heap_flags_field_symbol_name = L"Flags"s;
    std::wstring const heap_segment_first_entry_field_symbol_name = L"FirstEntry"s;
    std::wstring const heap_segment_last_entry_field_symbol_name = L"LastValidEntry"s;
    std::wstring const heap_total_memory_reserved_field_symbol_name = L"Counters.TotalMemoryReserved"s;
    std::wstring const heap_total_memory_committed_field_symbol_name = L"Counters.TotalMemoryCommitted"s;
    std::wstring const heap_total_memory_large_ucr_field_symbol_name = L"Counters.TotalMemoryLargeUCR"s;
    std::wstring const heap_total_size_in_virtual_blocks_field_symbol_name = L"Counters.TotalSizeInVirtualBlocks"s;
    std::wstring const heap_total_segments_field_symbol_name = L"Counters.TotalSegments"s;
    std::wstring const heap_total_ucrs_field_symbol_name = L"Counters.TotalUCRs"s;
    std::wstring const heap_encode_flag_mask_field_symbol_name = L"EncodeFlagMask"s;
    std::wstring const heap_encoding_field_symbol_name = L"Encoding"s;
    std::wstring const heap_ucr_list_field_symbol_name = L"UCRList"s;
    std::wstring const heap_ucr_list_flink_field_symbol_name = L"UCRList.Flink"s;
    std::wstring const heap_virtual_allocated_blocks_field_symbol_name = L"VirtualAllocdBlocks"s;
    std::wstring const heap_virtual_allocated_blocks_flink_field_symbol_name = L"VirtualAllocdBlocks.Flink"s;
    std::wstring const heap_free_lists_field_symbol_name = L"FreeLists"s;
    std::wstring const heap_free_lists_flink_field_symbol_name = L"FreeLists.Flink"s;
    std::wstring const heap_total_free_size_field_symbol_name = L"TotalFreeSize"s;
    std::wstring const heap_segment_list_field_symbol_name = L"SegmentList"s;
    std::wstring const heap_segment_list_flink_field_symbol_name = L"SegmentList.Flink"s;
    std::wstring const heap_segment_list_entry_field_symbol_name = L"SegmentListEntry"s;
    std::wstring const heap_segment_list_entry_flink_field_symbol_name = L"SegmentListEntry.Flink"s;
    std::wstring const heap_allocator_back_trace_index_field_symbol_name = L"AllocatorBackTraceIndex"s;
    std::wstring const heap_front_end_heap_type_field_symbol_name = L"FrontEndHeapType"s;
    std::wstring const heap_front_end_heap_field_symbol_name = L"FrontEndHeap"s;
    std::wstring const list_entry_flink_field_symbol_name = L"Flink"s;
    std::wstring const heap_entry_small_tag_index_field_symbol_name = L"SmallTagIndex"s;
    std::wstring const heap_entry_size_field_symbol_name = L"Size"s;
    std::wstring const heap_entry_flags_field_symbol_name = L"Flags"s;
    std::wstring const heap_entry_segment_offset_field_symbol_name = L"SegmentOffset"s;
    std::wstring const heap_entry_unused_bytes_field_symbol_name = L"UnusedBytes"s;
    std::wstring const heap_entry_previous_size_field_symbol_name = L"PreviousSize"s;
    std::wstring const heap_segment_segment_flags_field_symbol_name = L"SegmentFlags"s;
    std::wstring const heap_segment_number_of_pages_field_symbol_name = L"NumberOfPages"s;
    std::wstring const heap_segment_base_address_field_symbol_name = L"BaseAddress"s;
    std::wstring const heap_segment_number_of_un_committed_pages_field_symbol_name = L"NumberOfUnCommittedPages"s;
    std::wstring const heap_segment_number_of_un_committed_ranges_field_symbol_name = L"NumberOfUnCommittedRanges"s;
    std::wstring const heap_segment_segment_allocator_back_trace_index_field_symbol_name = L"SegmentAllocatorBackTraceIndex"s;
    std::wstring const heap_segment_ucr_segment_list_field_symbol_name = L"UCRSegmentList"s;
    std::wstring const heap_segment_ucr_segment_list_flink_field_symbol_name = L"UCRSegmentList.Flink"s;
    std::wstring const heap_ucr_descriptor_address_field_symbol_name = L"Address"s;
    std::wstring const heap_ucr_descriptor_size_field_symbol_name = L"Size"s;
    std::wstring const heap_ucr_descriptor_segment_entry_field_symbol_name = L"SegmentEntry"s;
    std::wstring const heap_ucr_descriptor_segment_entry_flink_field_symbol_name = L"SegmentEntry.Flink"s;
    std::wstring const heap_virtual_alloc_entry_reserve_size_field_symbol_name = L"ReserveSize"s;
    std::wstring const heap_virtual_alloc_entry_commit_size_field_symbol_name = L"CommitSize"s;
    std::wstring const heap_virtual_alloc_entry_busy_block_field_symbol_name = L"BusyBlock"s;
    std::wstring const heap_free_entry_heap_entry_field_symbol_name = L"HeapEntry"s;
    std::wstring const heap_free_entry_free_list_field_symbol_name = L"FreeList"s;
    std::wstring const lfh_heap_sub_segment_zones_field_symbol_name = L"SubSegmentZones"s;
    std::wstring const lfh_heap_sub_segment_zones_flink_field_symbol_name = L"SubSegmentZones.Flink"s;
    std::wstring const lfh_block_zone_next_index_field_symbol_name = L"NextIndex"s;
    std::wstring const lfh_block_zone_free_pointer_field_symbol_name = L"FreePointer"s;
    std::wstring const heap_subsegment_block_size_field_symbol_name = L"BlockSize"s;
    std::wstring const heap_subsegment_block_count_field_symbol_name = L"BlockCount"s;
    std::wstring const heap_subsegment_user_blocks_field_symbol_name = L"UserBlocks"s;
    std::wstring const heap_user_data_encoded_offsets_field_symbol_name = L"EncodedOffsets"s;
    std::wstring const heap_user_data_first_allocation_offset_field_symbol_name = L"FirstAllocationOffset"s;
}
