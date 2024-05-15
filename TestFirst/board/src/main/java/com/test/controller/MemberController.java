package com.test.controller;


import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;

import com.test.mapper.BoardMapper;

import com.test.entity.Member;

@Controller
public class MemberController {
	
		
	@Autowired
	BoardMapper mapper;
		
	@GetMapping("/member/memberList")
	public void listMember(Model model) {
			
		model.addAttribute("list", mapper.selectMemberList());
	}
	
	@GetMapping("/member/memberRegistry")
	public void getMemberRegistry() {}
	
	@PostMapping("/member/memberRegistry")
	public String postMemberRegistry(Member member) {
		
		mapper.insertMember(member.getUserid(), member.getUsername(), member.getAge());
		return "redirect:/member/memberList";
		
	}
	
//	public  MemberController(BoardMapper mBoardMapper ) {
//		this.mapper = mapper;
//	}
//	
}
	
