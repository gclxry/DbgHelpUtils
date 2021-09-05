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
    std::wstring const dph_heap_root_structure_symbol_name = L"ntdll!_DPH_HEAP_ROOT"s;
    std::wstring const rtl_balanced_links_structure_symbol_name = L"ntdll!_RTL_BALANCED_LINKS"s;
    std::wstring const dph_heap_block_structure_symbol_name = L"ntdll!_DPH_HEAP_BLOCK"s;
    std::wstring const rtl_stack_trace_entry_structure_symbol_name = L"ntdll!_RTL_STACK_TRACE_ENTRY"s;
    std::wstring const dph_block_information_structure_symbol_name = L"ntdll!_DPH_BLOCK_INFORMATION"s;
    std::wstring const segment_heap_structure_symbol_name = L"ntdll!_SEGMENT_HEAP"s;
    std::wstring const heap_seg_context_structure_symbol_name = L"ntdll!_HEAP_SEG_CONTEXT"s;
    std::wstring const heap_page_segment_structure_symbol_name = L"ntdll!_HEAP_PAGE_SEGMENT"s;
    std::wstring const heap_page_range_descriptor_structure_symbol_name = L"ntdll!_HEAP_PAGE_RANGE_DESCRIPTOR"s;
    std::wstring const rtl_rb_tree_structure_symbol_name = L"ntdll!_RTL_RB_TREE"s;
    std::wstring const rtl_balanced_node_structure_symbol_name = L"ntdll!_RTL_BALANCED_NODE"s;
    std::wstring const heap_vs_context_structure_symbol_name = L"ntdll!_HEAP_VS_CONTEXT"s;
    std::wstring const heap_vs_subsegment_structure_symbol_name = L"ntdll!_HEAP_VS_SUBSEGMENT"s;
    std::wstring const heap_vs_chunk_header_structure_symbol_name = L"ntdll!_HEAP_VS_CHUNK_HEADER"s;
    std::wstring const heap_vs_chunk_free_header_structure_symbol_name = L"ntdll!_HEAP_VS_CHUNK_FREE_HEADER"s;
    std::wstring const heap_large_alloc_structure_symbol_name = L"ntdll!_HEAP_LARGE_ALLOC_DATA"s;
    std::wstring const heap_lfh_context_structure_symbol_name = L"ntdll!_HEAP_LFH_CONTEXT"s;
    std::wstring const heap_lfh_bucket_structure_symbol_name = L"ntdll!_HEAP_LFH_BUCKET"s;
    std::wstring const heap_lfh_affinity_slot_structure_symbol_name = L"ntdll!_HEAP_LFH_AFFINITY_SLOT"s;
    std::wstring const heap_lfh_subsegment_structure_symbol_name = L"ntdll!_HEAP_LFH_SUBSEGMENT"s;
    std::wstring const heap_lfh_subsegment_encoded_offsets_structure_symbol_name = L"ntdll!_HEAP_LFH_SUBSEGMENT_ENCODED_OFFSETS"s;

    std::wstring const rtl_p_lfh_key_global_symbol_name = L"ntdll!RtlpLFHKey"s;
    std::wstring const av_rfp_dph_page_heap_list_global_symbol_name = L"verifier!AVrfpDphPageHeapList"s;
    std::wstring const rtl_p_heap_key_global_symbol_name = L"ntdll!RtlpHeapKey"s;
    std::wstring const rtl_p_hp_heap_globals_global_symbol_name = L"ntdll!RtlpHpHeapGlobals"s;

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
    std::wstring const heap_virtual_allocated_blocks_field_symbol_name = L"VirtualAllocdBlocks"s;
    std::wstring const heap_free_lists_field_symbol_name = L"FreeLists"s;
    std::wstring const heap_total_free_size_field_symbol_name = L"TotalFreeSize"s;
    std::wstring const heap_segment_list_field_symbol_name = L"SegmentList"s;
    std::wstring const heap_segment_list_entry_field_symbol_name = L"SegmentListEntry"s;
    std::wstring const heap_allocator_back_trace_index_field_symbol_name = L"AllocatorBackTraceIndex"s;
    std::wstring const heap_front_end_heap_type_field_symbol_name = L"FrontEndHeapType"s;
    std::wstring const heap_front_end_heap_field_symbol_name = L"FrontEndHeap"s;
    std::wstring const list_entry_flink_field_symbol_name = L"Flink"s;
    std::wstring const heap_entry_small_tag_index_field_symbol_name = L"SmallTagIndex"s;
    std::wstring const heap_entry_size_field_symbol_name = L"Size"s;
    std::wstring const heap_entry_flags_field_symbol_name = L"Flags"s;
    std::wstring const heap_entry_segment_offset_field_symbol_name = L"SegmentOffset"s;
    std::wstring const heap_entry_unused_bytes_field_symbol_name = L"UnusedBytes"s;
    std::wstring const heap_entry_unused_bytes_length_field_symbol_name = L"UnusedBytesLength"s;
    std::wstring const heap_entry_previous_size_field_symbol_name = L"PreviousSize"s;
    std::wstring const heap_segment_segment_flags_field_symbol_name = L"SegmentFlags"s;
    std::wstring const heap_segment_number_of_pages_field_symbol_name = L"NumberOfPages"s;
    std::wstring const heap_segment_base_address_field_symbol_name = L"BaseAddress"s;
    std::wstring const heap_segment_number_of_un_committed_pages_field_symbol_name = L"NumberOfUnCommittedPages"s;
    std::wstring const heap_segment_number_of_un_committed_ranges_field_symbol_name = L"NumberOfUnCommittedRanges"s;
    std::wstring const heap_segment_segment_allocator_back_trace_index_field_symbol_name = L"SegmentAllocatorBackTraceIndex"s;
    std::wstring const heap_segment_ucr_segment_list_field_symbol_name = L"UCRSegmentList"s;
    std::wstring const heap_ucr_descriptor_list_entry_field_symbol_name = L"ListEntry"s;
    std::wstring const heap_ucr_descriptor_address_field_symbol_name = L"Address"s;
    std::wstring const heap_ucr_descriptor_size_field_symbol_name = L"Size"s;
    std::wstring const heap_ucr_descriptor_segment_entry_field_symbol_name = L"SegmentEntry"s;
    std::wstring const heap_virtual_alloc_entry_entry_field_symbol_name = L"Entry"s;
    std::wstring const heap_virtual_alloc_entry_reserve_size_field_symbol_name = L"ReserveSize"s;
    std::wstring const heap_virtual_alloc_entry_commit_size_field_symbol_name = L"CommitSize"s;
    std::wstring const heap_virtual_alloc_entry_busy_block_field_symbol_name = L"BusyBlock"s;
    std::wstring const heap_free_entry_heap_entry_field_symbol_name = L"HeapEntry"s;
    std::wstring const heap_free_entry_free_list_field_symbol_name = L"FreeList"s;
    std::wstring const lfh_heap_sub_segment_zones_field_symbol_name = L"SubSegmentZones"s;
    std::wstring const lfh_block_zone_list_entry_field_symbol_name = L"ListEntry"s;
    std::wstring const lfh_block_zone_next_index_field_symbol_name = L"NextIndex"s;
    std::wstring const lfh_block_zone_free_pointer_field_symbol_name = L"FreePointer"s;
    std::wstring const heap_subsegment_block_size_field_symbol_name = L"BlockSize"s;
    std::wstring const heap_subsegment_block_count_field_symbol_name = L"BlockCount"s;
    std::wstring const heap_subsegment_user_blocks_field_symbol_name = L"UserBlocks"s;
    std::wstring const heap_user_data_encoded_offsets_field_symbol_name = L"EncodedOffsets"s;
    std::wstring const heap_user_data_first_allocation_offset_field_symbol_name = L"FirstAllocationOffset"s;
    std::wstring const dph_heap_root_next_heap_field_symbol_name = L"NextHeap"s;
    std::wstring const dph_heap_root_flags_field_symbol_name = L"HeapFlags"s;
    std::wstring const dph_heap_root_extra_flags_field_symbol_name = L"ExtraFlags"s;
    std::wstring const dph_heap_root_seed_field_symbol_name = L"Seed"s;
    std::wstring const dph_heap_root_normal_heap_field_symbol_name = L"NormalHeap"s;
    std::wstring const dph_heap_root_busy_nodes_table_field_symbol_name = L"BusyNodesTable"s;
    std::wstring const dph_heap_root_virtual_storage_list_head_field_symbol_name = L"pVirtualStorageListHead"s;
    std::wstring const dph_heap_root_virtual_storage_list_tail_field_symbol_name = L"pVirtualStorageListTail"s;
    std::wstring const dph_heap_root_virtual_storage_ranges_field_symbol_name = L"nVirtualStorageRanges"s;
    std::wstring const dph_heap_root_virtual_storage_bytes_field_symbol_name = L"nVirtualStorageBytes"s;
    std::wstring const dph_heap_root_busy_allocations_field_symbol_name = L"nBusyAllocations"s;
    std::wstring const dph_heap_root_busy_allocations_bytes_committed_field_symbol_name = L"nBusyAllocationBytesCommitted"s;
    std::wstring const dph_heap_root_free_allocations_list_head_field_symbol_name = L"pFreeAllocationListHead"s;
    std::wstring const dph_heap_root_free_allocations_list_tail_field_symbol_name = L"pFreeAllocationListTail"s;
    std::wstring const dph_heap_root_free_allocations_field_symbol_name = L"nFreeAllocations"s;
    std::wstring const dph_heap_root_free_allocations_bytes_committed_field_symbol_name = L"nFreeAllocationBytesCommitted"s;
    std::wstring const rtl_balanced_links_left_child_field_symbol_name = L"LeftChild"s;
    std::wstring const rtl_balanced_links_right_child_field_symbol_name = L"RightChild"s;
    std::wstring const dph_heap_block_virtual_block_field_symbol_name = L"pVirtualBlock"s;
    std::wstring const dph_heap_block_virtual_block_size_field_symbol_name = L"nVirtualBlockSize"s;
    std::wstring const dph_heap_block_user_allocation_field_symbol_name = L"pUserAllocation"s;
    std::wstring const dph_heap_block_user_requested_size_field_symbol_name = L"nUserRequestedSize"s;
    std::wstring const dph_heap_block_stack_trace_field_symbol_name = L"StackTrace"s;
    std::wstring const dph_heap_block_next_alloc_field_symbol_name = L"pNextAlloc"s;
    std::wstring const rtl_stack_trace_entry_index_field_symbol_name = L"Index"s;
    std::wstring const rtl_stack_trace_entry_depth_field_symbol_name = L"Depth"s;
    std::wstring const rtl_stack_trace_entry_back_trace_field_symbol_name = L"BackTrace"s;
    std::wstring const dph_block_information_start_stamp_field_symbol_name = L"StartStamp"s;
    std::wstring const segment_heap_signature_field_symbol_name = L"Signature"s;
    std::wstring const segment_heap_global_flags_field_symbol_name = L"GlobalFlags"s;
    std::wstring const segment_heap_mem_stats_total_reserved_pages_field_symbol_name = L"MemStats.TotalReservedPages"s;
    std::wstring const segment_heap_mem_stats_total_committed_pages_field_symbol_name = L"MemStats.TotalCommittedPages"s;
    std::wstring const segment_heap_mem_stats_free_committed_pages_field_symbol_name = L"MemStats.FreeCommittedPages"s;
    std::wstring const segment_heap_mem_stats_lfh_free_committed_pages_field_symbol_name = L"MemStats.LfhFreeCommittedPages"s;
    std::wstring const segment_heap_allocated_base_field_symbol_name = L"AllocatedBase"s;
    std::wstring const segment_heap_uncommitted_base_field_symbol_name = L"UncommittedBase"s;
    std::wstring const segment_heap_reserved_limit_field_symbol_name = L"ReservedLimit"s;
    std::wstring const segment_heap_large_alloc_metadata_field_symbol_name = L"LargeAllocMetadata"s;
    std::wstring const segment_heap_large_reserved_pages_field_symbol_name = L"LargeReservedPages"s;
    std::wstring const segment_heap_large_committed_pages_field_symbol_name = L"LargeCommittedPages"s;
    std::wstring const segment_heap_segment_contexts_field_symbol_name = L"SegContexts"s;
    std::wstring const segment_heap_vs_context_field_symbol_name = L"VsContext"s;
    std::wstring const segment_heap_lfh_context_field_symbol_name = L"LfhContext"s;
    std::wstring const segment_heap_seg_context_max_allocation_size_field_symbol_name = L"MaxAllocationSize"s;
    std::wstring const segment_heap_seg_context_segment_count_field_symbol_name = L"SegmentCount"s;
    std::wstring const segment_heap_seg_context_segment_mask_field_symbol_name = L"SegmentMask"s;
    std::wstring const segment_heap_seg_context_unit_shift_field_symbol_name = L"UnitShift"s;
    std::wstring const segment_heap_seg_context_pages_per_unit_shift_field_symbol_name = L"PagesPerUnitShift"s;
    std::wstring const segment_heap_seg_context_segment_list_head_field_symbol_name = L"SegmentListHead"s;
    std::wstring const segment_heap_seg_context_free_page_ranges_field_symbol_name = L"FreePageRanges"s;
    std::wstring const heap_page_segment_list_entry_field_symbol_name = L"ListEntry"s;
    std::wstring const heap_page_segment_signature_field_symbol_name = L"Signature"s;
    std::wstring const heap_page_segment_desc_array_field_symbol_name = L"DescArray"s;
    std::wstring const heap_page_range_descriptor_tree_node_field_symbol_name = L"TreeNode"s;
    std::wstring const heap_page_range_descriptor_unused_bytes_field_symbol_name = L"UnusedBytes"s;
    std::wstring const heap_page_range_descriptor_extra_present_field_symbol_name = L"ExtraPresent"s;
    std::wstring const heap_page_range_descriptor_range_flags_field_symbol_name = L"RangeFlags"s;
    std::wstring const heap_page_range_descriptor_range_flags_bits_field_symbol_name = L"RangeFlagBits"s;
    std::wstring const heap_page_range_descriptor_committed_page_count_field_symbol_name = L"CommittedPageCount"s;
    std::wstring const heap_page_range_descriptor_unit_offset_field_symbol_name = L"UnitOffset"s;
    std::wstring const heap_page_range_descriptor_unit_size_field_symbol_name = L"UnitSize"s;
    std::wstring const rtl_rb_tree_root_field_symbol_name = L"Root"s;
    std::wstring const rtl_balanced_node_left_field_symbol_name = L"Left"s;
    std::wstring const rtl_balanced_node_right_field_symbol_name = L"Right"s;
    std::wstring const heap_vs_context_free_chunk_tree_field_symbol_name = L"FreeChunkTree"s;
    std::wstring const heap_vs_context_subsegment_list_field_symbol_name = L"SubsegmentList"s;
    std::wstring const heap_vs_context_total_committed_units_field_symbol_name = L"TotalCommittedUnits"s;
    std::wstring const heap_vs_context_free_committed_units_field_symbol_name = L"FreeCommittedUnits"s;
    std::wstring const heap_vs_subsegment_list_entry_field_symbol_name = L"ListEntry"s;
    std::wstring const heap_vs_subsegment_size_field_symbol_name = L"Size"s;
    std::wstring const heap_vs_subsegment_signature_field_symbol_name = L"Signature"s;
    std::wstring const heap_vs_subsegment_full_commit_field_symbol_name = L"FullCommit"s;
    std::wstring const heap_vs_chunk_header_sizes_memory_cost_field_symbol_name = L"Sizes.MemoryCost"s;
    std::wstring const heap_vs_chunk_header_sizes_unsafe_prev_size_field_symbol_name = L"Sizes.UnsafePrevSize"s;
    std::wstring const heap_vs_chunk_header_sizes_unsafe_size_field_symbol_name = L"Sizes.UnsafeSize"s;
    std::wstring const heap_vs_chunk_header_sizes_allocated_field_symbol_name = L"Sizes.Allocated"s;
    std::wstring const heap_vs_chunk_header_encoded_segment_page_offset_field_symbol_name = L"EncodedSegmentPageOffset"s;
    std::wstring const heap_vs_chunk_header_unused_bytes_field_symbol_name = L"UnusedBytes"s;
    std::wstring const heap_vs_chunk_header_skip_during_walk_field_symbol_name = L"SkipDuringWalk"s;
    std::wstring const heap_vs_chunk_header_spare_field_symbol_name = L"Spare"s;
    std::wstring const heap_vs_chunk_header_allocated_chunk_bits_field_symbol_name = L"AllocatedChunkBits"s;
    std::wstring const heap_vs_chunk_free_header_node_field_symbol_name = L"Node"s;
    std::wstring const heap_large_alloc_tree_node_field_symbol_name = L"TreeNode"s;
    std::wstring const heap_large_alloc_virtual_address_field_symbol_name = L"VirtualAddress"s;
    std::wstring const heap_large_alloc_unused_bytes_field_symbol_name = L"UnusedBytes"s;
    std::wstring const heap_large_alloc_extra_present_field_symbol_name = L"ExtraPresent"s;
    std::wstring const heap_large_alloc_guard_page_count_field_symbol_name = L"GuardPageCount"s;
    std::wstring const heap_large_alloc_guard_page_alignment_field_symbol_name = L"GuardPageAlignment"s;
    std::wstring const heap_large_alloc_spare_field_symbol_name = L"Spare"s;
    std::wstring const heap_large_alloc_allocated_pages_field_symbol_name = L"AllocatedPages"s;
    std::wstring const heap_lfh_context_max_affinity_field_symbol_name = L"MaxAffinity"s;
    std::wstring const heap_lfh_context_config_max_block_size_field_symbol_name = L"Config.MaxBlockSize"s;
    std::wstring const heap_lfh_context_config_with_old_page_crossing_blocks_field_symbol_name = L"Config.WitholdPageCrossingBlocks"s;
    std::wstring const heap_lfh_context_config_disable_randomization_field_symbol_name = L"Config.DisableRandomization"s;
    std::wstring const heap_lfh_context_buckets_field_symbol_name = L"Buckets"s;
    std::wstring const heap_lfh_bucket_bucket_index_field_symbol_name = L"State.BucketIndex"s;
    std::wstring const heap_lfh_bucket_slot_count_field_symbol_name = L"State.SlotCount"s;
    std::wstring const heap_lfh_bucket_total_block_count_field_symbol_name = L"TotalBlockCount"s;
    std::wstring const heap_lfh_bucket_total_subsegment_count_field_symbol_name = L"TotalSubsegmentCount"s;
    std::wstring const heap_lfh_bucket_reciprocal_block_size_field_symbol_name = L"ReciprocalBlockSize"s;
    std::wstring const heap_lfh_bucket_shift_field_symbol_name = L"Shift"s;
    std::wstring const heap_lfh_bucket_proc_affinity_mapping_field_symbol_name = L"ProcAffinityMapping"s;
    std::wstring const heap_lfh_bucket_affinity_slots_field_symbol_name = L"AffinitySlots"s;
    std::wstring const heap_lfh_affinity_slot_bucket_index_field_symbol_name = L"State.BucketIndex"s;
    std::wstring const heap_lfh_affinity_slot_slot_index_field_symbol_name = L"State.SlotIndex"s;
    std::wstring const heap_lfh_affinity_slot_available_subsegment_count_field_symbol_name = L"State.AvailableSubsegmentCount"s;
    std::wstring const heap_lfh_affinity_slot_available_subsegment_list_field_symbol_name = L"State.AvailableSubsegmentList"s;
    std::wstring const heap_lfh_affinity_slot_full_subsegment_list_field_symbol_name = L"State.FullSubsegmentList"s;
    std::wstring const heap_lfh_subsegment_list_entry_field_symbol_name = L"ListEntry"s;
    std::wstring const heap_lfh_subsegment_free_count_field_symbol_name = L"FreeCount"s;
    std::wstring const heap_lfh_subsegment_block_count_field_symbol_name = L"BlockCount"s;
    std::wstring const heap_lfh_subsegment_location_field_symbol_name = L"Location"s;
    std::wstring const heap_lfh_subsegment_witheld_block_count_field_symbol_name = L"WitheldBlockCount"s;
    std::wstring const heap_lfh_subsegment_block_offsets_field_symbol_name = L"BlockOffsets"s;
    std::wstring const heap_lfh_subsegment_commit_unit_shift_field_symbol_name = L"CommitUnitShift"s;
    std::wstring const heap_lfh_subsegment_commit_unit_count_field_symbol_name = L"CommitUnitCount"s;
    std::wstring const heap_lfh_subsegment_block_bitmap_field_symbol_name = L"BlockBitmap"s;
    std::wstring const heap_lfh_subsegment_encoded_offsets_block_size_field_symbol_name = L"BlockSize"s;
    std::wstring const heap_lfh_subsegment_encoded_offsets_first_block_offset_field_symbol_name = L"FirstBlockOffset"s;
}
