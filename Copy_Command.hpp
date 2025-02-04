struct Target_Structure
{
	__int32 Identifier;

	void* Self;

	__int8 Priority;

	float Distance;

	__int32 Tick_Number;
};

std::vector<Target_Structure> Sorted_Target_List;

void* Get_Studio_Header(void* Entity)
{
	using Get_Studio_Header_Type = void*(__thiscall*)(void* Entity);

	return Get_Studio_Header_Type((unsigned __int32)Client_Module + 8512)(Entity);
}

void* Get_Hitbox_Set(Target_Structure* Target, float(*Bones)[3][4], float Time)
{
	using Setup_Bones_Type = __int8(__thiscall*)(void* Entity, void* Bones, __int32 Maximum_Bones, __int32 Mask, float Current_Time);

	if (Setup_Bones_Type((unsigned __int32)Client_Module + 246656)((void*)((unsigned __int32)Target->Self + 4), Bones, 128, 524032, Time) == 1)
	{
		void* Studio_Header = *(void**)Get_Studio_Header(Target->Self);

		return (void*)((unsigned __int32)Studio_Header + *(__int32*)((unsigned __int32)Studio_Header + 176));
	}

	return nullptr;
}

void* Original_Copy_Command_Caller;

void __thiscall Redirected_Copy_Command(void* Unknown_Parameter, Command_Structure* Command)
{
	Extended_Command_Structure* Extended_Command = &Extended_Commands[Command->Command_Number % 150];

	Extended_Command->Extra_Commands = 0;

	Extended_Command->Sequence_Shift = 0;

	void* Local_Player = *(void**)((unsigned __int32)Client_Module + 7498712);

	Global_Variables_Structure* Global_Variables = *(Global_Variables_Structure**)((unsigned __int32)Client_Module + 7096744);

	if (Extra_Commands == -1)
	{
		*(float*)((unsigned __int32)Local_Player + 16) = Global_Variables->Interval_Per_Tick;

		*(__int32*)((unsigned __int32)Local_Player + 20) = Command->Command_Number;

		if ((Command->Buttons & 524288) == 524288)
		{
			Extended_Command->Extra_Commands = max(0, Extra_Commands = std::clamp(Interface_Extra_Commands.Integer, (__int32)(0.06f / Global_Variables->Interval_Per_Tick + 0.5f), 14));

			*(float*)((unsigned __int32)Local_Player + 16) *= 1.f + Extended_Command->Extra_Commands * Interface_Interpolate_Extra_Commands.Integer;
		}

		__int32 Variable_Number = 0;

		Traverse_Variables_Label:
		{
			void* Variable = *(void**)(*(unsigned __int32*)((unsigned __int32)Local_Player + 24) + Variable_Number * 12 + 8);

			*(float*)((unsigned __int32)Variable + 36) = *(float*)((unsigned __int32)Local_Player + 16);

			Variable_Number += 1;

			if (Variable_Number != *(__int32*)((unsigned __int32)Local_Player + 36))
			{
				goto Traverse_Variables_Label;
			}
		}
	}

	if (*(__int8*)((unsigned __int32)Local_Player + 327) == 0)
	{
		Command->Buttons |= 4194304 * (Command->Command_Number % 2);

		float Move_Angles[3] =
		{
			Command->Angles[0],

			Command->Angles[1]
		};

		static float Previous_Move_Angle_Y;

		if ((Command->Buttons & 2) + *(__int8*)((unsigned __int32)Local_Player + 324) == 4)
		{
			Command->Move[0] = 0;

			if (*(void**)((unsigned __int32)Local_Player + 316) == INVALID_HANDLE_VALUE)
			{
				Command->Buttons &= ~2;
			}
			else
			{
				Command->Buttons &= ~(*(__int32*)((unsigned __int32)Local_Player + 5028) & 2);
			}

			float Difference = __builtin_remainderf(Move_Angles[1] - Previous_Move_Angle_Y, 360.f);

			Previous_Move_Angle_Y = Move_Angles[1];

			float* Velocity = (float*)((unsigned __int32)Local_Player + 256);

			if (__builtin_fabsf(Difference) < __builtin_atan2f(30.f, __builtin_hypotf(Velocity[0], Velocity[1])) * 180.f / 3.1415927f)
			{
				float Strafe_Angle = __builtin_remainderf(Move_Angles[1] - __builtin_atan2f(Velocity[1], Velocity[0]) * 180.f / 3.1415927f, 360.f);

				if (__builtin_signbitf(Strafe_Angle) == 0)
				{
					Command->Move[1] = -450.f;
				}
				else
				{
					Command->Move[1] = 450.f;
				}

				Move_Angles[1] -= Strafe_Angle;
			}
			else
			{
				if (__builtin_signbitf(Difference) == 0)
				{
					Command->Move[1] = -450.f;
				}
				else
				{
					Command->Move[1] = 450.f;
				}
			}
		}
		else
		{
			Previous_Move_Angle_Y = Move_Angles[1];
		}

		float Previous_Move[2];

		Byte_Manager::Copy_Bytes(1, Previous_Move, sizeof(Previous_Move), Command->Move);

		float Desired_Move_Forward[3];

		float Desired_Move_Right[3];

		Angle_Vectors(Move_Angles, Desired_Move_Forward, Desired_Move_Right, nullptr);

		Desired_Move_Forward[2] = 0.f;

		Vector_Normalize(Desired_Move_Forward);

		Desired_Move_Right[2] = 0.f;

		Vector_Normalize(Desired_Move_Right);

		float Desired_Move[2] =
		{
			Desired_Move_Forward[0] * Command->Move[0] + Desired_Move_Right[0] * Command->Move[1],

			Desired_Move_Forward[1] * Command->Move[0] + Desired_Move_Right[1] * Command->Move[1]
		};

		auto Correct_Movement = [&]() -> void
		{
			float Move_Forward[3];

			float Move_Right[3];

			Angle_Vectors(Command->Angles, Move_Forward, Move_Right, nullptr);

			Move_Forward[2] = 0.f;

			Vector_Normalize(Move_Forward);

			Move_Right[2] = 0.f;

			Vector_Normalize(Move_Right);

			float Divider = Move_Forward[0] * Move_Right[1] - Move_Right[0] * Move_Forward[1];

			Command->Move[0] = (Desired_Move[0] * Move_Right[1] - Move_Right[0] * Desired_Move[1]) / Divider;

			Command->Move[1] = (Move_Forward[0] * Desired_Move[1] - Desired_Move[0] * Move_Forward[1]) / Divider;
		};

		Correct_Movement();

		Extended_Command_Structure* Initial_Extended_Command = &Extended_Commands[*(__int32*)((unsigned __int32)Local_Player + 20) % 150];

		void* Network_Channel = *(void**)(*(unsigned __int32*)((unsigned __int32)Engine_Module + 4352236) + 24);

		auto Sequence_Shift = [&](__int32 Reserve) -> void
		{
			if (Initial_Extended_Command->Sequence_Shift == 0)
			{
				__int32 Sequence_Shift = (*(__int32*)((unsigned __int32)Local_Player + 5324) - Extended_Command->Extra_Commands + ~-150) / 150 * 150 + (Reserve * 150);

				if (Sequence_Shift > 0)
				{
					*(__int32*)((unsigned __int32)Network_Channel + 8) += Sequence_Shift;

					Extended_Command->Sequence_Shift += Sequence_Shift;

					__int32 Command_Number = Command->Command_Number;

					Traverse_Command_Batch_Label:
					{
						Command_Number -= 1;

						if (Command_Number >= *(__int32*)((unsigned __int32)Local_Player + 20))
						{
							Extended_Commands[Command_Number % 150].Sequence_Shift = Extended_Command->Sequence_Shift;

							goto Traverse_Command_Batch_Label;
						}
					}
				}
			}
		};

		static __int32 Accumulative_Correction;

		auto Disable_Clock_Correction = [&](__int32 Queue) -> void
		{
			if (Queue > 0)
			{
				if (Extended_Command == Initial_Extended_Command)
				{
					Extended_Command->Extra_Commands = 0;

					Extra_Commands = max((__int32)(0.06f / Global_Variables->Interval_Per_Tick + 0.5f), Queue);
				}
				else
				{
					Accumulative_Correction += 1;
				}

				if (Initial_Extended_Command->Extra_Commands == 0)
				{
					*(__int32*)((unsigned __int32)Network_Channel + 16) = -1;

					*(__int32*)((unsigned __int32)Network_Channel + 28) = 255;
				}
			}
		};

		auto Correct_Extended_Command = [&]() -> void
		{
			if (*(__int32*)((unsigned __int32)Network_Channel + 16) != -1)
			{
				Extended_Command->Extra_Commands += Accumulative_Correction;

				Accumulative_Correction = 0;
			}

			Extended_Command->Sequence_Shift = Initial_Extended_Command->Sequence_Shift;
		};

		if (*(__int32*)((unsigned __int32)Local_Player + 228) == 3)
		{
			if (*(__int8*)((unsigned __int32)Local_Player + 7322) == 0)
			{
				if (*(void**)((unsigned __int32)Local_Player + 10008) == INVALID_HANDLE_VALUE)
				{
					__int8 Is_Jockey_Victim = *(void**)((unsigned __int32)Local_Player + 10056) != INVALID_HANDLE_VALUE;

					if ((*(void**)((unsigned __int32)Local_Player + 10012) != INVALID_HANDLE_VALUE) + (*(void**)((unsigned __int32)Local_Player + 10024) != INVALID_HANDLE_VALUE) + Is_Jockey_Victim != 0)
					{
						Command->Buttons |= Is_Jockey_Victim * 2;

						Disable_Clock_Correction(Interface_Extra_Commands_Action.Integer);
					}
				}
				else
				{
					Sequence_Shift(2);
				}
			}
			else
			{
				if (*(__int32*)((unsigned __int32)Local_Player + 7324) == 0)
				{
					Sequence_Shift(-2);
				}
			}

			Correct_Extended_Command();
		}
		else
		{
			__int8 Action = *(void**)((unsigned __int32)Local_Player + 7076) == *(void**)((unsigned __int32)Local_Player + 376);

			__int8 Reviving = *(void**)((unsigned __int32)Local_Player + 8076) != INVALID_HANDLE_VALUE;

			if ((*(float*)((unsigned __int32)Local_Player + 4604) + 800.f * Global_Variables->Interval_Per_Tick >= 560.f) + *(__int8*)((unsigned __int32)Local_Player + 8068) + *(__int8*)((unsigned __int32)Local_Player + 9708) != 0)
			{
				Sequence_Shift(2);
			}
			else
			{
				if (Action + Reviving != 0)
				{
					Disable_Clock_Correction(Interface_Extra_Commands_Action.Integer);
				}
			}

			Correct_Extended_Command();

			*(__int32*)((unsigned __int32)Local_Player + 5620) = Command->Command_Number;

			void* Prediction = (void*)((unsigned __int32)Client_Module + 8072728);

			*(__int8*)((unsigned __int32)Prediction + 8) = 1;

			*(__int8*)((unsigned __int32)Prediction + 24) = 0;

			using Set_Host_Type = void(__thiscall*)(void* Move_Helper, void* Player);

			Set_Host_Type((unsigned __int32)Client_Module + 1331184)((void*)((unsigned __int32)Client_Module + 7174888), Local_Player);

			Redirected_Run_Command(Prediction, Local_Player, Command, (void*)((unsigned __int32)Client_Module + 7174888));

			Set_Host_Type((unsigned __int32)Client_Module + 1331184)((void*)((unsigned __int32)Client_Module + 7174888), nullptr);

			*(__int8*)((unsigned __int32)Prediction + 8) = 0;

			__int32 Block_Buttons = 2049;

			if ((*(__int32*)((unsigned __int32)Local_Player + 324) & 9) == 0)
			{
				if ((*(__int32*)((unsigned __int32)Local_Player + 5020) & 32) * (Action ^ 1) == 0)
				{
					using Can_Attack_Type = __int8(__thiscall*)(void* Player);

					if (Can_Attack_Type((unsigned __int32)Client_Module + 2541696)(Local_Player) == 1)
					{
						void* Weapon = *(__int8*)((unsigned __int32)Local_Player + 7867) == 0 ? *(void**)((unsigned __int32)Client_Module + 7644532 + (((*(unsigned __int32*)((unsigned __int32)Local_Player + 4228) & 4095) - 4097) << 4)) : nullptr;

						if (Weapon == nullptr)
						{
							Block_Buttons = 2048;
						}
						else
						{
							__int8 Cancelable_Shove = 1 + (*(float*)((unsigned __int32)Local_Player + 7336) < Global_Variables->Current_Time) * (*(float*)((unsigned __int32)Weapon + 2404) <= Global_Variables->Current_Time);

							__int32 Weapon_Identifier = Get_Identifier(Weapon, 1, 0);

							if ((Weapon_Identifier == 105) + (Weapon_Identifier == 121) == 0)
							{
								static std::unordered_set<__int32> Grenades = { 106, 118, 129 };

								if (Grenades.contains(Weapon_Identifier) == 1)
								{
									Cancelable_Shove = min((*(__int16*)((unsigned __int32)Weapon + 3304) == 0) + (*(float*)((unsigned __int32)Weapon + 3308) == 0.f), Cancelable_Shove);
								}
							}
							else
							{
								Cancelable_Shove = min(1 + (*(float*)((unsigned __int32)Weapon + 3312) == -1.f), Cancelable_Shove);
							}

							__int8 In_Shove = Global_Variables->Current_Time >= *(float*)((unsigned __int32)Local_Player + 7904);

							if (Global_Variables->Current_Time >= *(float*)((unsigned __int32)Weapon + 2704))
							{
								In_Shove = *(__int8*)((unsigned __int32)Weapon + 2720);
							}

							__int32 Ammo = *(__int32*)((unsigned __int32)Weapon + 2436);

							static void* Predicted_Shot;

							using Get_Weapon_Data_Type = void*(__thiscall*)(void* Weapon);

							void* Weapon_Data = Get_Weapon_Data_Type((unsigned __int32)Client_Module + 86432)(Weapon);

							__int8 Is_Melee = *(__int32*)((unsigned __int32)Weapon_Data + 352) * (*(__int32*)((unsigned __int32)Weapon_Data + 348) ^ 1) <= 1;

							__int8 Reloading = *(__int8*)((unsigned __int32)Weapon + 2493);

							__int8 Can_Attack = 0;

							if (Weapon_Identifier == 39)
							{
								Can_Attack = (min(Chainsaw_Cycles * 0.46153846f * Global_Variables->Interval_Per_Tick, 1.f) > 0.95f) * (In_Shove ^ 1);
							}
							else
							{
								Can_Attack = (*(float*)((unsigned __int32)Weapon + 2400) <= Global_Variables->Current_Time) * (Ammo > 0 - Is_Melee * 2) * (Reloading ^ 1);

								if ((*(double*)((unsigned __int32)Weapon + 3392) == 0.) * Weapon_Identifier == 153)
								{
									Can_Attack *= *(float*)((unsigned __int32)Weapon + 3400) <= Global_Variables->Current_Time;
								}
							}

							__int32 Entity_Number = 1;

							using Get_Interpolation_Time_Type = float(__cdecl*)();

							float Interpolation_Time = Get_Interpolation_Time_Type((unsigned __int32)Engine_Module + 594000)();

							Sorted_Target_List.clear();

							auto Get_Target_Time = [&](Target_Structure* Target) -> float
							{
								if (Interface_Target_On_Simulation.Integer == 0)
								{
									return *(float*)((unsigned __int32)Local_Player + 336);
								}

								return *(float*)((unsigned __int32)Target->Self + 336);
							};

							Traverse_Entity_List_Label:
							{
								void* Entity = *(void**)((unsigned __int32)Client_Module + 7644532 + ((Entity_Number - 4097) << 4));

								if (Entity != nullptr)
								{
									if (Entity != Local_Player)
									{
										__int32 Identifier = Get_Identifier(Entity, 0, 0);

										if (Identifier != -1)
										{
											if (*(__int32*)((unsigned __int32)Entity + 228) % 2 != *(__int32*)((unsigned __int32)Local_Player + 228) % 2)
											{
												float* Local_Origin = (float*)((unsigned __int32)Local_Player + 292);

												float* Entity_Origin = (float*)((unsigned __int32)Entity + 292);

												float Time = *(float*)((unsigned __int32)Entity + 336) + Interpolation_Time;

												Target_Structure Target =
												{
													Identifier,

													Entity,

													(__int8)(Identifier == 270 ? *(void**)((unsigned __int32)Entity + 8040) == *(void**)((unsigned __int32)Local_Player + 376) : 0),

													__builtin_powf(Local_Origin[0] - Entity_Origin[0], 2.f) + __builtin_powf(Local_Origin[1] - Entity_Origin[1], 2.f) + __builtin_powf(Local_Origin[2] - Entity_Origin[2], 2.f),

													(__int32)(Time / Global_Variables->Interval_Per_Tick + 0.5f)
												};

												if (*(float*)((unsigned __int32)Entity + 16) != Get_Target_Time(&Target))
												{
													if (Identifier == 277)
													{
														if (*(float*)((unsigned __int32)Entity + 4844) == 1.f)
														{
															Sorted_Target_List.push_back(Target);
														}
													}
													else
													{
														Sorted_Target_List.push_back(Target);
													}
												}
											}
										}
									}
								}

								if (Entity_Number != *(__int32*)((unsigned __int32)Client_Module + 7644568))
								{
									Entity_Number += 1;

									goto Traverse_Entity_List_Label;
								}
							}

							auto Target_List_Sort_Prepare = [](Target_Structure& X, Target_Structure& Y) -> __int8
							{
								return X.Priority < Y.Priority;
							};

							std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Prepare);

							auto Target_List_Sort_Finish = [](Target_Structure& X, Target_Structure& Y) -> __int8
							{
								if (X.Priority > Y.Priority)
								{
									return 1;
								}

								return X.Distance < Y.Distance;
							};

							std::sort(Sorted_Target_List.begin(), Sorted_Target_List.end(), Target_List_Sort_Finish);

							size_t Target_Number = 0;

							using Get_Eye_Position_Type = void(__thiscall*)(void* Entity, float* Eye_Position);

							float Eye_Position[3];

							Get_Eye_Position_Type((unsigned __int32)Client_Module + 108512)(Local_Player, Eye_Position);

							Target_Structure* Shove_Target = nullptr;

							if (Cancelable_Shove + In_Shove > 1)
							{
								if (*(__int8*)((unsigned __int32)Local_Player + 8070) * (Weapon_Identifier == 231) == 0)
								{
									if (Interface_Shotgun_Shove.Integer == 1)
									{
										if ((Weapon_Identifier - 148) % 14 == 0)
										{
											if ((void*)((unsigned __int32)Weapon + Ammo) == Predicted_Shot)
											{
												Predicted_Shot = nullptr;

												Command->Buttons |= 2048;

												Block_Buttons = 1;
											}
										}
									}

									__int8 Is_Chainsaw = Weapon_Identifier == 39;

									__int8 Holstering = 0;

									if (Is_Chainsaw == 0)
									{
										using Get_Sequence_Duration_Type = float(__thiscall*)(void* Entity, void* Studio_Header, __int32 Sequence);

										using Select_Sequence_Type = __int32(__thiscall*)(void* Entity, __int32 Activity);

										using Translate_Activity_Type = __int32(__thiscall**)(void* Weapon, __int32 Activity);

										using Get_Deploy_Activity_Type = __int32(__thiscall**)(void* Weapon);

										Holstering = (min(*(float*)((unsigned __int32)Local_Player + 3872), *(float*)((unsigned __int32)Weapon + 2412)) + Get_Sequence_Duration_Type((unsigned __int32)Client_Module + 180400)(Weapon, Get_Studio_Header(Weapon), Select_Sequence_Type((unsigned __int32)Client_Module + 202896)(Weapon, (*Translate_Activity_Type(*(unsigned __int32*)Weapon + 1692))(Weapon, (*Get_Deploy_Activity_Type(*(unsigned __int32*)Weapon + 1600))(Weapon)))) > Global_Variables->Current_Time) * (Can_Attack ^ 1);
									}
									else
									{
										Is_Chainsaw = Can_Attack * (Command->Buttons & 1);
									}

									Shove_Traverse_Sorted_Target_List_Label:
									{
										if (Target_Number != Sorted_Target_List.size())
										{
											Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

											__int8 Forced = 0;

											if (((Command->Buttons & 2048) + Reloading + Holstering + Is_Melee * (Is_Chainsaw ^ 1)) * (Action + Reviving ^ 1) != 0)
											{
												if ((Target->Identifier ^ 72) % 348 >= 72)
												{
													Forced = 1;

													goto Shove_Label;
												}
											}

											if ((270 - Target->Identifier ^ Target->Identifier - 263) >= 0)
											{
												Shove_Label:
												{
													__int8 Infected = (Target->Identifier == 264) * (Forced ^ 1);

													__int32 Gender = *(__int32*)((unsigned __int32)Target->Self + 52);

													if ((Infected ^ 1) + (Gender == 15) != 0)
													{
														if (__builtin_strstr(Get_Sequence_Name(Target->Self), "hove") == nullptr)
														{
															using Perform_Shove_Trace = __int8(__thiscall*)(void* Weapon, float* Direction);

															float* Target_Origin = Get_Center(Target->Self);

															float Direction[3] =
															{
																Target_Origin[0] - Eye_Position[0],

																Target_Origin[1] - Eye_Position[1],

																Target_Origin[2] - Eye_Position[2]
															};

															Vector_Normalize(Direction);

															*(float*)((unsigned __int32)Weapon + 2724) = 75.f;

															*(__int32*)((unsigned __int32)Weapon + 3248) = 0;

															Perform_Trace_Target = Target->Self;

															Perform_Trace_Damage = 0.f;

															Perform_Shove_Trace((unsigned __int32)Client_Module + 3220512)(Weapon, Direction);

															Perform_Trace_Target = nullptr;

															if (Perform_Trace_Damage == 1.f)
															{
																if (Action == 0)
																{
																	Command->Tick_Number = Target->Tick_Number;

																	Command->Angles[0] = __builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f;

																	Command->Angles[1] = __builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f;

																	if (Cancelable_Shove == 1)
																	{
																		float Shove_Multiplier = min((Global_Variables->Current_Time - *(float*)((unsigned __int32)Weapon + 2704) + *(float*)((unsigned __int32)Weapon + 2700)) / *(float*)((unsigned __int32)Weapon + 2700), 1.f);

																		Command->Angles[1] += -45.f * Shove_Multiplier + 45.f * (1.f - Shove_Multiplier);
																	}
																	else
																	{
																		Command->Angles[1] += 45.f;
																	}

																	Command->Buttons |= 2048;

																	Block_Buttons = 1;

																	Cancelable_Shove = (Gender * Interface_Riot_Deprioritize.Integer * (Forced ^ 1)) == 15;

																	*(float*)((unsigned __int32)Target->Self + 16) = Get_Target_Time(Target);

																	goto Shove_Found_Target_Label;
																}

																Cancelable_Shove = 0;

																goto Shove_Found_Target_Label;
															}
														}
													}
												}
											}

											Target_Number += 1;

											goto Shove_Traverse_Sorted_Target_List_Label;

											Shove_Found_Target_Label:
											{
												Shove_Target = Target;
											}
										}
									}
								}
							}

							if (Cancelable_Shove != 0)
							{
								if (Reviving + (Can_Attack ^ 1) == 0)
								{
									Target_Structure* Aim_Target = nullptr;

									if (Is_Melee == 0)
									{
										__int8 Compensate_Burst = 0;

										if (Weapon_Identifier == 2)
										{
											Command->Command_Number = -2134739495;

											Command->Random_Seed = 11144000;
										}
										else
										{
											if (Weapon_Identifier == 148)
											{
												Command->Command_Number = -2139542887;

												Command->Random_Seed = 1246243990;
											}
											else
											{
												if (Weapon_Identifier == 153)
												{
													Compensate_Burst = *(double*)((unsigned __int32)Weapon + 3392) != 0.;

													Command->Buttons |= Compensate_Burst;
												}
												else
												{
													if ((163 - Weapon_Identifier ^ Weapon_Identifier - 162) == 1)
													{
														Command->Command_Number = -2139097805;

														Command->Random_Seed = 494641349;
													}
												}
											}
										}

										if (Compensate_Burst == 0)
										{
											using Update_Spread_Type = void(__thiscall*)(void* Weapon);

											Update_Spread_Type((unsigned __int32)Client_Module + 3197648)(Weapon);
										}

										Target_Number = 0;

										Aim_Traverse_Sorted_Target_List_Label:
										{
											if (Target_Number != Sorted_Target_List.size())
											{
												Target_Structure* Target = &Sorted_Target_List.at(Target_Number);

												float Bones[128][3][4];

												void* Hitbox_Set = Get_Hitbox_Set(Target, Bones, Global_Variables->Current_Time);

												if (Hitbox_Set != nullptr)
												{
													auto Perform_Trace = [&](float* Angles) -> __int8
													{
														using Fire_Bullet_Type = void(__thiscall*)(void* Player, float X, float Y, float Z, float* Angles, __int32 Identifier, void* Unknown_Parameter);

														__int32 Bullets = *(__int32*)((unsigned __int32)Weapon_Data + 2520);

														if (Interface_Penetration_Damage.Floating_Point == 0)
														{
															*(__int32*)((unsigned __int32)Weapon_Data + 2520) = 1;
														}

														Perform_Trace_Target = Target->Self;

														Perform_Trace_Damage = 0.f;

														void* Previous_Audio_Device = *(void**)((unsigned __int32)Engine_Module + 5050008);

														*(void**)((unsigned __int32)Engine_Module + 5050008) = nullptr;

														*(__int32*)((unsigned __int32)Client_Module + 7075944) = Command->Random_Seed;

														*(__int32*)((unsigned __int32)Client_Module + 7683464) = 1;

														*(__int32*)((unsigned __int32)Client_Module + 7689576) = 0;

														*(__int32*)((unsigned __int32)Client_Module + 8175320) = 0;

														*(__int32*)((unsigned __int32)Client_Module + 8175392) = 0;

														using Get_Weapon_Identifier_Type = __int32(__thiscall**)(void* Weapon);

														Fire_Bullet_Type((unsigned __int32)Client_Module + 3103776)(Local_Player, Eye_Position[0], Eye_Position[1], Eye_Position[2], Angles, (*Get_Weapon_Identifier_Type(*(unsigned __int32*)Weapon + 1532))(Weapon), nullptr);

														*(__int32*)((unsigned __int32)Client_Module + 8175392) = 1;

														*(__int32*)((unsigned __int32)Client_Module + 8175320) = 1;

														*(__int32*)((unsigned __int32)Client_Module + 7689576) = 1;

														*(__int32*)((unsigned __int32)Client_Module + 7683464) = 0;

														*(void**)((unsigned __int32)Engine_Module + 5050008) = Previous_Audio_Device;

														Perform_Trace_Target = nullptr;

														*(__int32*)((unsigned __int32)Weapon_Data + 2520) = Bullets;

														return (Perform_Trace_Damage >= Interface_Penetration_Damage.Floating_Point) * (Perform_Trace_Damage != 0.f);
													};

													static std::unordered_map<__int32, __int32> Hitboxes =
													{
														{ 0, 10 },

														{ 13, 0 },

														{ 99, 9 },

														{ 263, 10 },

														{ 264, 15 },

														{ 265, 4 },

														{ 270, 10 },

														{ 272, 4 },

														{ 276, 12 },

														{ 277, 10 }
													};

													void* Hitbox = (void*)((unsigned __int32)Hitbox_Set + 12 + Hitboxes[Target->Identifier] * 68);

													float* Hitbox_Minimum = (float*)((unsigned __int32)Hitbox + 8);

													float* Hitbox_Maximum = (float*)((unsigned __int32)Hitbox + 20);

													float Hitbox_Center[3]
													{
														(Hitbox_Minimum[0] + Hitbox_Maximum[0]) / 2.f,

														(Hitbox_Minimum[1] + Hitbox_Maximum[1]) / 2.f,

														(Hitbox_Minimum[2] + Hitbox_Maximum[2]) / 2.f
													};

													float Target_Origin[3] =
													{
														Bones[*(__int32*)Hitbox][0][0] * Hitbox_Center[0] + Bones[*(__int32*)Hitbox][0][1] * Hitbox_Center[1] + Bones[*(__int32*)Hitbox][0][2] * Hitbox_Center[2] + Bones[*(__int32*)Hitbox][0][3],

														Bones[*(__int32*)Hitbox][1][0] * Hitbox_Center[0] + Bones[*(__int32*)Hitbox][1][1] * Hitbox_Center[1] + Bones[*(__int32*)Hitbox][1][2] * Hitbox_Center[2] + Bones[*(__int32*)Hitbox][1][3],

														Bones[*(__int32*)Hitbox][2][0] * Hitbox_Center[0] + Bones[*(__int32*)Hitbox][2][1] * Hitbox_Center[1] + Bones[*(__int32*)Hitbox][2][2] * Hitbox_Center[2] + Bones[*(__int32*)Hitbox][2][3]
													};

													float Direction[3] =
													{
														Target_Origin[0] - Eye_Position[0],

														Target_Origin[1] - Eye_Position[1],

														Target_Origin[2] - Eye_Position[2]
													};

													Vector_Normalize(Direction);

													float Angles[3] =
													{
														__builtin_atan2f(-Direction[2], __builtin_hypotf(Direction[0], Direction[1])) * 180.f / 3.1415927f,

														__builtin_atan2f(Direction[1], Direction[0]) * 180.f / 3.1415927f
													};

													if (Perform_Trace(Angles) == 1)
													{
														Command->Tick_Number = Target->Tick_Number;

														Byte_Manager::Copy_Bytes(1, Command->Angles, sizeof(Angles), Angles);

														Command->Buttons |= 1;

														*(float*)((unsigned __int32)Target->Self + 16) = Get_Target_Time(Target);

														goto Aim_Found_Target_Label;
													}
												}

												Target_Number += 1;

												goto Aim_Traverse_Sorted_Target_List_Label;

												Aim_Found_Target_Label:
												{
													Aim_Target = Target;
												}
											}
										}
									}

									if ((Command->Buttons & 1) == 1)
									{
										if (Shove_Target != nullptr)
										{
											*(float*)((unsigned __int32)Shove_Target->Self + 16) = 0.f;

											if (Aim_Target != nullptr)
											{
												*(float*)((unsigned __int32)Aim_Target->Self + 16) = Get_Target_Time(Aim_Target);
											}
										}

										if (Is_Melee == 0)
										{
											*(__int32*)((unsigned __int32)Client_Module + 7075944) = Command->Random_Seed;

											using Random_Type = float(__cdecl*)(char* Name, float Minimum, float Maximum, void* Unknown_Parameter);

											float Maximum_Spread = *(float*)((unsigned __int32)Weapon + 3340);

											float* Recoil = (float*)((unsigned __int32)Local_Player + 4612);

											Command->Angles[0] -= Random_Type((unsigned __int32)Client_Module + 1756592)((char*)"CTerrorGun::FireBullet HorizSpread", -Maximum_Spread, Maximum_Spread, nullptr) + Recoil[0];

											Command->Angles[1] -= Random_Type((unsigned __int32)Client_Module + 1756592)((char*)"CTerrorGun::FireBullet VertSpread", -Maximum_Spread, Maximum_Spread, nullptr) + Recoil[1];

											Command->Angles[2] -= Recoil[2];
										}

										Predicted_Shot = (void*)((unsigned __int32)Weapon + Ammo - 1);

										Block_Buttons = 2048;
									}
								}

								if (Block_Buttons == 2049)
								{
									Block_Buttons = 2048 * (Cancelable_Shove == 1) + (Can_Attack ^ 1);
								}
							}
						}
					}
				}
			}

			Command->Buttons &= ~Block_Buttons;

			Byte_Manager::Copy_Bytes(1, Command->Move, sizeof(Previous_Move), Previous_Move);

			Correct_Movement();

			*(__int8*)((unsigned __int32)__builtin_frame_address(0) + 235) = max(Extra_Commands <= 0, *(__int32*)((unsigned __int32)Network_Channel + 16) == -1);
		}
	}

	Command->Buttons &= ~524288;

	(decltype(&Redirected_Copy_Command)(Original_Copy_Command_Caller))(Unknown_Parameter, Command);
}