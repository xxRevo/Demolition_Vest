class SuicideVest_ColorBase extends Clothing {

	protected const float TIME_TRIGGER_INITIAL_DELAY_SECS = 0.1;
	protected const float TIME_TRIGGER_TIMER_BASED_DELAY_SECS = 1.0;
	protected const float TIME_TRIGGER_DELAY_SECS = 0.3;
    protected static const string SLOT_TRIGGER_REMOTE = "TriggerRemoteDetonator_Receiver";
	protected static const string SLOT_TRIGGER_KITCHEN_TIMER = "TriggerKitchenTimer";
	protected static const string SLOT_TRIGGER_ALARM_CLOCK = "TriggerAlarmClock";
    protected static const string SLOT_EXPLOSIVE_A = "VestGrenadeA";
	protected const int SLOT_TRIGGERS_COUNT = 3;
	protected const string SLOT_TRIGGERS[SLOT_TRIGGERS_COUNT] = {
		SLOT_TRIGGER_ALARM_CLOCK,
		SLOT_TRIGGER_KITCHEN_TIMER,
		SLOT_TRIGGER_REMOTE
	};

	protected bool m_Armed;
	protected ref RemotelyActivatedItemBehaviour m_RAIB;

	void SuicideVest_ColorBase() {
		m_RAIB = new RemotelyActivatedItemBehaviour(this);

		RegisterNetSyncVariableInt("m_RAIB.m_PairDeviceNetIdLow");
		RegisterNetSyncVariableInt("m_RAIB.m_PairDeviceNetIdHigh");
		RegisterNetSyncVariableBool("m_Armed");
	}

    override void OnWasAttached( EntityAI parent, int slot_id )
    {
        PlayerBase player = PlayerBase.Cast( parent );

        if( player )
        {
            player.GetInventory().SetSlotLock( InventorySlots.GetSlotIdFromString( "Vest" ), true );
            LockExplosivesSlot();
            LockTriggerSlots();
        }
        super.OnWasAttached( parent, slot_id );
    }
    
	RemotelyActivatedItemBehaviour GetRemotelyActivatedItemBehaviour()
	{
		return m_RAIB;
	}

	protected void SetArmed(bool state)
	{
		m_Armed = state;
		SetSynchDirty();
	}

	protected void OnTriggerAttached(EntityAI entity)
	{
		UpdateLED(ERemoteDetonatorLEDState.LIT);
		
		if (entity.IsInherited(ClockBase))
			Arm();
		
		LockTriggerSlots();
		LockExplosivesSlot();
	}
	
	protected void OnTriggerDetached(EntityAI entity)
	{
		UpdateLED(ERemoteDetonatorLEDState.OFF);
	}

    bool GetArmed() {
        return m_Armed;
    }

	bool IsTimerDetonable()
	{
		return true;
	}

    bool HasLockedTriggerSlots()
	{
		foreach (string triggerSlot : SLOT_TRIGGERS)
			return GetInventory().GetSlotLock(InventorySlots.GetSlotIdFromString(triggerSlot));
		
		return false;
	}

	void Arm()
	{
		SetArmed(true);
	}

    void LockTriggerSlots()
	{
		foreach (string triggerSlotName : SLOT_TRIGGERS)
			GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString(triggerSlotName), true);
	}
	
	void UnlockTriggerSlots()
	{
		foreach (string triggerSlotName : SLOT_TRIGGERS)
			GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString(triggerSlotName), false);
	}

    void LockExplosivesSlot()
	{	
        GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString(SLOT_EXPLOSIVE_A), true);
	}
	
	void UnlockExplosivesSlot()
	{	
        GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString(SLOT_EXPLOSIVE_A), false);
	}

	void UpdateLED(int pState)
	{
		RemoteDetonatorReceiver receiver = RemoteDetonatorReceiver.Cast(FindAttachmentBySlotName(SLOT_TRIGGER_REMOTE));
		if (receiver)
			receiver.UpdateLED(pState, true);
	}

	void PairRemote(notnull EntityAI trigger)
	{
		m_RAIB.Pair(trigger);
	}

	EntityAI GetPairDevice()
	{
		return m_RAIB.GetPairDevice();
	}

    bool CanBeArmed()
	{
        if (GetArmed())
			return false;

		if (!HasLockedTriggerSlots())
			return false;

		EntityAI explosive = GetInventory().FindAttachmentByName(SLOT_EXPLOSIVE_A);
		if (explosive)
            return true;
		
		return false;
	}

    override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
        if (GetInventory().FindAttachmentByName(SLOT_EXPLOSIVE_A) != null) {
            Grenade_Base explosive = GetInventory().FindAttachmentByName(SLOT_EXPLOSIVE_A);
	 	    explosive.ActivateImmediate();
        }
        //InitiateExplosion();
		//UnpairRemote();	
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);

		switch (slot_name)
		{
			case SLOT_TRIGGER_ALARM_CLOCK:
			case SLOT_TRIGGER_KITCHEN_TIMER:
			case SLOT_TRIGGER_REMOTE:
				OnTriggerAttached(FindAttachmentBySlotName(slot_name));
				break;
		}
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		switch (slot_name)
		{
			case SLOT_TRIGGER_ALARM_CLOCK:
			case SLOT_TRIGGER_KITCHEN_TIMER:
			case SLOT_TRIGGER_REMOTE:
				OnTriggerDetached(FindAttachmentBySlotName(slot_name));
				break;
		}
	}

	override void OnActivatedByItem(notnull ItemBase item)
	{
		if (GetInventory().FindAttachmentByName(SLOT_TRIGGER_KITCHEN_TIMER) != null) {
			Grenade_Base explosive = GetInventory().FindAttachmentByName(SLOT_EXPLOSIVE_A);
	 	    explosive.ActivateImmediate();
		}
	}
	
/*
    protected void InitiateExplosion()
	{
		int count = m_AmmoTypes.Count();
		for (int i = 0; i < count; i++)
		{
			Explode(DamageType.EXPLOSION, m_AmmoTypes[i]);
		}

		OnExplode();
	}
*/
}

