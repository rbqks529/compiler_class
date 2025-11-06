## 1. Android 알림 시스템 이해하기

### 1.1 Android Notification의 개념

**알림(Notification)**은 앱이 사용자에게 중요한 정보를 전달하는 UI 요소입니다.

#### 알림이 표시되는 위치
- **알림 표시줄(Notification Bar)**: 화면 상단
- **알림 서랍(Notification Drawer)**: 위에서 아래로 스와이프 시 표시
- **잠금 화면**: 설정에 따라 표시

#### 알림의 구성 요소
```
┌────────────────────────────────────┐
│  [아이콘]  타이머 완료              │  ← 제목 (Title)
│           설정한 시간이 모두 지났습니다  │  ← 내용 (Content Text)
└────────────────────────────────────┘
```

### 1.2 Notification Channel (Android 8.0+)

Android 8.0(API 26)부터 **Notification Channel**이 필수입니다.

#### Notification Channel이란?
- 알림을 **카테고리별로 그룹화**하는 개념
- 사용자가 **채널별로 알림 설정**을 제어 가능
- 예: "타이머 알림", "메시지 알림", "프로모션 알림"

#### Importance Level
| Level | 설명 | 동작 |
|-------|------|------|
| `IMPORTANCE_HIGH` | 높음 | 소리 + 진동 + 헤드업 알림 |
| `IMPORTANCE_DEFAULT` | 기본 | 소리 + 진동 |
| `IMPORTANCE_LOW` | 낮음 | 소리 없음 |

### 1.3 PendingIntent 개념

**PendingIntent**는 다른 앱(시스템)이 우리 앱의 Intent를 실행할 수 있도록 권한을 위임하는 객체입니다.

#### 일반 Intent vs PendingIntent

```kotlin
// 일반 Intent - 알림에서 사용 불가
val intent = Intent(context, MainActivity::class.java)
// 시스템이 우리 앱을 실행할 권한이 없음!

// PendingIntent - 알림에서 사용 가능
val pendingIntent = PendingIntent.getActivity(
    context,
    0,
    intent,
    PendingIntent.FLAG_IMMUTABLE
)
// 시스템에 권한을 위임하여 나중에 실행 가능!
```

#### FLAG_IMMUTABLE (Android 12+)

Android 12부터 보안 강화를 위해 **FLAG_IMMUTABLE** 또는 **FLAG_MUTABLE**을 명시해야 합니다.

```kotlin
val flags = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
    PendingIntent.FLAG_IMMUTABLE or PendingIntent.FLAG_UPDATE_CURRENT
} else {
    PendingIntent.FLAG_UPDATE_CURRENT
}
```

- **FLAG_IMMUTABLE**: 변경 불가능 (대부분의 경우 권장)
- **FLAG_UPDATE_CURRENT**: 기존 PendingIntent가 있으면 업데이트

### 1.4 Android 권한 시스템

#### Runtime Permission (Android 6.0+)

Android 6.0부터 **위험한 권한**은 런타임에 사용자 동의를 받아야 합니다.

#### Notification Permission (Android 13+)

Android 13부터 **POST_NOTIFICATIONS** 권한이 추가되었습니다.

```kotlin
// Android 13 이전: 권한 불필요, 자동 허용
// Android 13+: 명시적 권한 요청 필요

if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
    // 권한 요청 로직
}
```

---

## 2. 프로젝트 현황 파악

### 2.1 현재 프로젝트 구조

```
app/src/main/java/com/example/kuit6_notification/
├── MainActivity.kt                 # 진입점
├── model/
│   └── TimerState.kt              # Idle, Running, Paused, Completed
├── ui/
│   ├── components/
│   │   ├── TimerDisplay.kt        # 원형 타이머 UI
│   │   ├── TimerControls.kt       # 시작/일시정지/리셋 버튼
│   │   └── TimeInputSection.kt    # 프리셋 버튼 (10초, 30초...)
│   ├── screen/
│   │   └── TimerScreen.kt         # 메인 화면
│   └── theme/                     # Material3 테마
├── util/
│   └── TimeFormatter.kt           # 시간 변환 유틸
└── viewmodel/
    └── TimerViewModel.kt          # 타이머 비즈니스 로직
```

### 2.2 현재 타이머 동작 흐름

```
1. 사용자가 프리셋 버튼 클릭 (예: "10초")
   ↓
2. TimerViewModel.setSeconds(10) 호출
   ↓
3. "시작" 버튼 클릭
   ↓
4. TimerViewModel.startTimer() 호출
   ↓
5. startCountdown() 내부에서 50ms마다 카운트다운
   ↓
6. remainingMillis가 0이 되면
   → _timerState.value = TimerState.Completed
   → 현재는 여기서 끝!
```

### 2.3 우리가 추가할 기능

타이머 완료 시점(6번)에 **알림 표시** 기능을 추가합니다.

```
6. remainingMillis가 0이 되면
   → _timerState.value = TimerState.Completed
   → notificationHelper.showCompletedNotification()  ← 추가!
```

---

## 3. 알림 구현 설계

### 3.1 필요한 컴포넌트

| 컴포넌트 | 역할 | 파일 위치 |
|----------|------|----------|
| **NotificationHelper** | 알림 생성 및 관리 | `util/NotificationHelper.kt` |

### 3.2 알림 흐름도

```
┌─────────────────────────────────────────────────────────┐
│                    타이머 완료                          │
│              TimerViewModel.startCountdown()            │
└─────────────────┬───────────────────────────────────────┘
                  │
                  ▼
┌─────────────────────────────────────────────────────────┐
│         NotificationHelper.showCompletedNotification()  │
│         - 권한 체크 (Android 13+)                      │
│         - 알림 채널 생성                                │
│         - 알림 빌드 (제목, 내용, 아이콘)                │
│         - NotificationManager.notify() 호출             │
│         - 예외 처리                                     │
└─────────────────┬───────────────────────────────────────┘
                  │
                  ▼
┌─────────────────────────────────────────────────────────┐
│                  알림바에 표시                          │
│  [아이콘]  타이머 완료                                  │
│           설정한 시간이 모두 지났습니다                 │
└─────────────────┬───────────────────────────────────────┘
                  │
              사용자 클릭
                  │
                  ▼
┌─────────────────────────────────────────────────────────┐
│            MainActivity 실행 (앱 열림)                  │
└─────────────────────────────────────────────────────────┘
```

### 3.3 간단한 알림 구조

이번 강의에서는 **기본 알림만** 구현합니다:
- 알림 클릭 시 앱 열기
- 제목, 내용, 아이콘
- 권한 체크 및 예외 처리

---

## 4. 단계별 구현

### Step 1: NotificationHelper.kt 구현

**목적**: 알림 생성, 표시, 제거를 담당하는 헬퍼 클래스

**경로**: `app/src/main/java/com/example/kuit6_notification/util/NotificationHelper.kt`

```kotlin
package com.example.kuit6_notification.util

import android.Manifest
import android.app.Notification
import android.app.NotificationChannel
import android.app.NotificationManager
import android.app.PendingIntent
import android.content.Context
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Build
import android.util.Log
import androidx.core.app.ActivityCompat
import androidx.core.app.NotificationCompat
import com.example.kuit6_notification.MainActivity
import com.example.kuit6_notification.R

class NotificationHelper(private val context: Context) {

    private val notificationManager =
        context.getSystemService(Context.NOTIFICATION_SERVICE) as NotificationManager

    companion object {
        // Notification Channel
        private const val NOTIFICATION_CHANNEL_ID = "timer_channel"
        private const val NOTIFICATION_CHANNEL_NAME = "타이머 알림"

        // Notification ID
        private const val TIMER_NOTIFICATION_ID = 1001
    }

    init {
        createNotificationChannel()
    }

    /**
     * Notification Channel 생성 (Android 8.0+)
     *
     * Android 8.0부터 알림을 표시하려면 먼저 Notification Channel을 생성해야 합니다.
     * 채널은 앱 설치 후 최초 1회만 생성하면 되며, 중복 생성해도 문제없습니다.
     */
    private fun createNotificationChannel() {
        // Android 8.0(API 26) 미만에서는 채널이 필요 없음
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            val channel = NotificationChannel(
                NOTIFICATION_CHANNEL_ID,               // 채널 ID
                NOTIFICATION_CHANNEL_NAME,             // 채널 이름 (사용자에게 표시)
                NotificationManager.IMPORTANCE_HIGH    // 중요도: 높음 (소리, 진동, 헤드업)
            ).apply {
                description = "타이머 완료 알림"
                enableVibration(true)                  // 진동 활성화
                vibrationPattern = longArrayOf(0, 500, 250, 500)  // 진동 패턴 (ms)
            }
            notificationManager.createNotificationChannel(channel)
        }
    }

    /**
     * 타이머 완료 알림 표시
     *
     * 권한 체크 → 알림 빌드 → 알림 표시 순서로 동작합니다.
     * 권한이 없거나 예외가 발생하면 조용히 실패합니다.
     */
    fun showCompletedNotification() {
        // Android 13+ 권한 체크
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            if (ActivityCompat.checkSelfPermission(
                    context,
                    Manifest.permission.POST_NOTIFICATIONS
                ) != PackageManager.PERMISSION_GRANTED
            ) {
                Log.w("NotificationHelper", "알림 권한이 허용되지 않았습니다")
                return  // 권한 없으면 조용히 종료
            }
        }

        runCatching {
            val notification = NotificationCompat.Builder(context, NOTIFICATION_CHANNEL_ID)
                .setContentTitle("타이머 완료")                    // 알림 제목
                .setContentText("설정한 시간이 모두 지났습니다")    // 알림 내용
                .setSmallIcon(R.drawable.ic_launcher_foreground)  // 작은 아이콘 (필수)
                .setContentIntent(createContentIntent())          // 알림 클릭 시 실행할 Intent
                .setAutoCancel(true)                              // 알림 클릭 시 자동 제거
                .setPriority(NotificationCompat.PRIORITY_HIGH)    // 우선순위: 높음
                .build()

            // 알림 표시
            notificationManager.notify(TIMER_NOTIFICATION_ID, notification)
        }.onSuccess {
            Log.d("NotificationHelper", "알림이 표시되었습니다")
        }.onFailure { e ->
            when (e) {
                is SecurityException -> Log.e("NotificationHelper", "알림 표시 중 보안 예외 발생", e)
                else -> Log.e("NotificationHelper", "알림 표시 중 예외 발생", e)
            }
        }
    }

    /**
     * 알림 클릭 시 실행할 PendingIntent 생성
     *
     * 알림을 클릭하면 MainActivity가 열립니다.
     */
    private fun createContentIntent(): PendingIntent {
        val intent = Intent(context, MainActivity::class.java).apply {
            // FLAG_ACTIVITY_NEW_TASK: 새로운 Task에서 Activity 실행
            // FLAG_ACTIVITY_CLEAR_TASK: 기존 Task의 모든 Activity 제거
            flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
        }

        val flags = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Android 6.0+: FLAG_IMMUTABLE 사용 가능
            // FLAG_IMMUTABLE: PendingIntent 생성 후 변경 불가 (보안 강화)
            // FLAG_UPDATE_CURRENT: 기존 PendingIntent가 있으면 Intent만 업데이트
            PendingIntent.FLAG_IMMUTABLE or PendingIntent.FLAG_UPDATE_CURRENT
        } else {
            PendingIntent.FLAG_UPDATE_CURRENT
        }

        return PendingIntent.getActivity(context, 0, intent, flags)
    }

    /**
     * 알림 제거
     *
     * NotificationManager.cancel()을 호출하여 알림을 제거합니다.
     */
    fun cancelNotification() {
        notificationManager.cancel(TIMER_NOTIFICATION_ID)
    }
}
```

#### 코드 설명
**1. 권한 체크 추가**
```kotlin
if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
    if (ActivityCompat.checkSelfPermission(...) != PERMISSION_GRANTED) {
        Log.w("NotificationHelper", "알림 권한이 허용되지 않았습니다")
        return  // 권한 없으면 조용히 종료
    }
}
```
- Android 13+에서 권한 체크 필수
- 권한 없으면 알림 표시하지 않음
- 로그로 권한 없음 기록

**2. 예외 처리 추가 (runCatching 사용)**
```kotlin
runCatching {
    // 알림 빌드 및 표시
    notificationManager.notify(...)
}.onSuccess {
    Log.d("NotificationHelper", "알림이 표시되었습니다")
}.onFailure { e ->
    when (e) {
        is SecurityException -> Log.e("NotificationHelper", "알림 표시 중 보안 예외 발생", e)
        else -> Log.e("NotificationHelper", "알림 표시 중 예외 발생", e)
    }
}
```
- `runCatching`: Kotlin의 Result API를 사용한 함수형 예외 처리
- `onSuccess`: 성공 시 실행 (알림 표시 성공 로그)
- `onFailure`: 실패 시 실행 (SecurityException 및 일반 예외 처리)
- try-catch보다 간결하고 Kotlin스러운 방식
- 앱 크래시 방지


#### 핵심 개념 정리
**1. NotificationChannel (Android 8.0+)**
```kotlin
NotificationChannel(채널ID, 채널이름, 중요도)
```
- **IMPORTANCE_HIGH**: 소리 + 진동 + 헤드업 알림
- 사용자가 설정에서 채널별로 알림 on/off 가능

**2. NotificationCompat.Builder**
```kotlin
NotificationCompat.Builder(context, 채널ID)
    .setContentTitle()   // 제목
    .setContentText()    // 내용
    .setSmallIcon()      // 아이콘 (필수!)
```

**3. PendingIntent 플래그**
- **FLAG_IMMUTABLE**: 생성 후 변경 불가 (Android 12+ 필수)
- **FLAG_UPDATE_CURRENT**: 기존 것이 있으면 Intent만 업데이트
- **FLAG_ACTIVITY_NEW_TASK**: 새로운 Task에서 Activity 실행
- **FLAG_ACTIVITY_CLEAR_TASK**: 기존 Task 정리

**4. setAutoCancel(true)**
- 알림을 클릭하면 자동으로 제거됨
- 사용자가 직접 스와이프로 제거하지 않아도 됨

---

### Step 2: AndroidManifest.xml 수정

**목적**: 알림 권한 추가

**경로**: `app/src/main/AndroidManifest.xml`

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:tools="http://schemas.android.com/tools">

    <!-- Android 13+ 알림 권한 -->
    <uses-permission android:name="android.permission.POST_NOTIFICATIONS" />

    <application
        android:allowBackup="true"
        android:dataExtractionRules="@xml/data_extraction_rules"
        android:fullBackupContent="@xml/backup_rules"
        android:icon="@mipmap/ic_launcher"
        android:label="@string/app_name"
        android:roundIcon="@mipmap/ic_launcher_round"
        android:supportsRtl="true"
        android:theme="@style/Theme.Kuit6_Notification">

        <activity
            android:name=".MainActivity"
            android:exported="true"
            android:label="@string/app_name"
            android:theme="@style/Theme.Kuit6_Notification">
            <intent-filter>
                <action android:name="android.intent.action.MAIN" />
                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>

</manifest>
```

#### 코드 설명

**POST_NOTIFICATIONS 권한**
```xml
<uses-permission android:name="android.permission.POST_NOTIFICATIONS" />
```
- Android 13(API 33)부터 필수
- Runtime Permission이므로 코드에서도 요청해야 함
- Android 12 이하에서는 자동 허용됨

---

### Step 3: TimerViewModel.kt 수정

**목적**: 타이머 완료 시 알림 표시

**경로**: `app/src/main/java/com/example/kuit6_notification/viewmodel/TimerViewModel.kt`

#### 3.1 import 추가

```kotlin
import com.example.kuit6_notification.util.NotificationHelper
```

#### 3.2 NotificationHelper 인스턴스 추가

```kotlin
class TimerViewModel(application: Application) : AndroidViewModel(application) {

    // NotificationHelper 인스턴스 생성
    private val notificationHelper = NotificationHelper(application)

    // 기존 코드...
    private val _timerState = MutableStateFlow<TimerState>(TimerState.Idle)
```

**왜 AndroidViewModel을 사용하나요?**
- `AndroidViewModel`은 `Application` 객체를 생성자로 받음
- `NotificationHelper`는 Context가 필요하므로 `application`을 전달
- 일반 `ViewModel`은 Context를 가질 수 없음 (메모리 누수 방지)

#### 3.3 startCountdown() 메서드 수정

```kotlin
private fun startCountdown(startMillis: Long) {
    timerJob?.cancel()
    timerJob = viewModelScope.launch {
        var remainingMillis = startMillis
        val updateInterval = 50L

        while (remainingMillis > 0) {
            delay(updateInterval)
            remainingMillis -= updateInterval

            if (remainingMillis <= 0) {
                _timerState.value = TimerState.Completed
                // 알림 표시 (권한 체크 및 예외 처리는 NotificationHelper 내부에서)
                notificationHelper.showCompletedNotification()
            } else {
                _timerState.value = TimerState.Running(remainingMillis)
            }
        }
    }
}
```

#### 코드 설명

**타이머 완료 시점**
```kotlin
if (remainingMillis <= 0) {
    _timerState.value = TimerState.Completed       // 상태 변경
    notificationHelper.showCompletedNotification()  // 알림 표시
}
```

**권한 체크를 ViewModel에서 하지 않는 이유**
- NotificationHelper가 내부적으로 권한 체크
- ViewModel은 비즈니스 로직에 집중
- 관심사의 분리 (Separation of Concerns)

---

### Step 4: TimerScreen.kt 수정

**목적**: Android 13+ 알림 권한 요청

**경로**: `app/src/main/java/com/example/kuit6_notification/ui/screen/TimerScreen.kt`

#### 4.1 import 추가

```kotlin
import android.Manifest
import android.content.pm.PackageManager
import android.os.Build
import android.util.Log
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.ui.platform.LocalContext
import androidx.core.content.ContextCompat
```

#### 4.2 TimerScreen 함수 수정

```kotlin
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun TimerScreen(
    viewModel: TimerViewModel = viewModel()
) {
    val context = LocalContext.current
    val timerState by viewModel.timerState.collectAsState()
    val hours by viewModel.hours.collectAsState()
    val minutes by viewModel.minutes.collectAsState()
    val seconds by viewModel.seconds.collectAsState()

    // Android 13+ 알림 권한 요청
    val notificationPermissionLauncher = rememberLauncherForActivityResult(
        contract = ActivityResultContracts.RequestPermission()
    ) { isGranted ->
        if (isGranted) {
            Log.d("TimerScreen", "알림 권한 허용")
        } else {
            Log.d("TimerScreen", "알림 권한 거부 - 알림이 표시되지 않습니다")
        }
    }

    // 앱 시작 시 권한 확인
    LaunchedEffect(Unit) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            val hasPermission = ContextCompat.checkSelfPermission(
                context,
                Manifest.permission.POST_NOTIFICATIONS
            ) == PackageManager.PERMISSION_GRANTED

            if (!hasPermission) {
                // 권한이 없으면 요청
                notificationPermissionLauncher.launch(
                    Manifest.permission.POST_NOTIFICATIONS
                )
            }
        }
        // Android 13 미만에서는 권한 요청 불필요
    }

    Scaffold(
        // 기존 UI 코드...
    )
}
```

#### 코드 설명

**1. Runtime Permission 요청**

```kotlin
// 권한 요청 런처 생성
val notificationPermissionLauncher = rememberLauncherForActivityResult(
    contract = ActivityResultContracts.RequestPermission()
) { isGranted ->
    // 권한 허용/거부 결과
}
```

**ActivityResultContracts.RequestPermission()**
- Compose에서 권한 요청을 위한 Contract
- `launch(permission)`로 권한 요청 다이얼로그 표시
- 결과는 람다로 전달 (`isGranted`)

**2. LaunchedEffect(Unit)**

```kotlin
LaunchedEffect(Unit) {
    // 앱 시작 시 한 번만 실행
}
```
- `Unit`을 키로 사용하면 **최초 1회만 실행**
- 권한 확인은 앱 시작 시 한 번만 하면 됨

**3. Android 버전 체크**

```kotlin
if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU)
```
- `TIRAMISU` = Android 13 (API 33)
- Android 13 이상에서만 권한 요청
- Android 12 이하는 자동 허용

---

## 5. 테스트 및 검증

### 5.1 빌드

```bash
./gradlew assembleDebug
```

BUILD SUCCESSFUL이 나오면 정상입니다.

### 5.2 테스트 시나리오

#### 시나리오 1: 앱 시작 및 권한 요청
1. 앱 설치 후 실행
2. **Android 13+**: 알림 권한 요청 다이얼로그 표시 → "허용" 클릭
3. **Android 12 이하**: 자동 허용, 다이얼로그 없음

#### 시나리오 2: 타이머 완료 알림 (권한 허용)
1. 프리셋 "10초" 클릭
2. "시작" 버튼 클릭
3. 10초 대기
4. 알림바에 "타이머 완료" 알림 표시 확인
5. Logcat에서 "알림이 표시되었습니다" 로그 확인

#### 시나리오 3: 타이머 완료 알림 (권한 거부)
1. 설정에서 알림 권한 거부
2. 타이머 10초 실행
3. 알림 표시 안 됨 (정상)
4. Logcat에서 "알림 권한이 허용되지 않았습니다" 로그 확인

#### 시나리오 4: 알림 클릭
1. 타이머 완료 후 알림 표시
2. 알림 클릭
3. 앱이 열림
4. 알림이 자동으로 제거됨

#### 시나리오 5: 앱이 백그라운드일 때
1. 타이머 시작
2. 홈 버튼으로 앱을 백그라운드로 보냄
3. 타이머 완료 대기
4. 알림이 표시되는지 확인
5. 알림 클릭 시 앱이 다시 열리는지 확인

### 5.3 확인 사항

- 알림 표시
- 권한 처리
- 알림 클릭
- 예외 처리

### 5.4 디버깅 팁

**알림이 표시되지 않을 때**
1. Logcat 확인: "알림 권한이 허용되지 않았습니다" 로그 확인
2. 설정 → 앱 → 권한에서 알림 권한 확인
3. NotificationChannel이 생성되었는지 확인 (설정 → 앱 → 알림)
4. Logcat에서 예외 로그 확인

**권한 요청이 표시되지 않을 때**
1. Android 버전이 13+ (TIRAMISU)인지 확인
2. 이미 권한을 허용/거부했는지 확인 (앱 삭제 후 재설치)
3. Manifest에 POST_NOTIFICATIONS 권한이 있는지 확인

---

## 6. 트러블슈팅

### 문제 1: 알림이 표시되지 않음

**증상**
- 타이머 완료 후 알림이 안 뜸
- Logcat에 아무 로그도 없음

**원인**
1. Android 13+에서 권한 거부
2. NotificationChannel ID 오타
3. 알림 우선순위가 너무 낮음

**해결**
1. Logcat 확인: `adb logcat -s NotificationHelper`
2. "알림 권한이 허용되지 않았습니다" 로그가 있으면 → 권한 허용
3. Channel ID 확인: `NOTIFICATION_CHANNEL_ID` 철자 확인
4. Importance 확인: `IMPORTANCE_HIGH` 사용

---

### 문제 2: Android 12에서 PendingIntent 크래시

**증상**
```
java.lang.IllegalArgumentException:
Targeting S+ requires that one of FLAG_IMMUTABLE or FLAG_MUTABLE be specified
```

**원인**
- Android 12+에서 FLAG_IMMUTABLE 또는 FLAG_MUTABLE 필수

**해결**
```kotlin
val flags = if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
    PendingIntent.FLAG_IMMUTABLE or PendingIntent.FLAG_UPDATE_CURRENT
} else {
    PendingIntent.FLAG_UPDATE_CURRENT
}
```

---

### 문제 3: 알림 권한 요청이 계속 표시됨

**증상**
- 앱을 실행할 때마다 권한 요청 다이얼로그가 뜸
- 이미 허용했는데도 계속 요청

**원인**
- 권한 확인 로직 문제
- LaunchedEffect 키가 잘못됨

**해결**
```kotlin
LaunchedEffect(Unit) {  // Unit을 키로 사용 (최초 1회만)
    if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
        val hasPermission = ContextCompat.checkSelfPermission(...)
        if (!hasPermission) {  // 권한이 없을 때만 요청
            notificationPermissionLauncher.launch(...)
        }
    }
}
```

---

### 문제 4: 권한 거부 시 앱 크래시

**증상**
- 권한 거부 후 타이머 완료 시 앱이 종료됨
- Logcat에 SecurityException

**원인**
- NotificationHelper에서 권한 체크 누락

**해결**
- 이미 구현됨! showCompletedNotification()에서 권한 체크
- runCatching으로 SecurityException 처리

---

### 문제 5: 알림 클릭해도 앱이 안 열림

**증상**
- 알림을 클릭해도 아무 반응 없음

**원인**
- PendingIntent 설정 오류
- Intent 플래그 누락

**해결**
```kotlin
val intent = Intent(context, MainActivity::class.java).apply {
    flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
}

val pendingIntent = PendingIntent.getActivity(
    context,
    0,
    intent,
    PendingIntent.FLAG_IMMUTABLE or PendingIntent.FLAG_UPDATE_CURRENT
)
```

---

## 7. 추가 학습 자료

### 7.1 공식 문서
- [Android Notification 가이드](https://developer.android.com/develop/ui/views/notifications)
- [PendingIntent 가이드](https://developer.android.com/reference/android/app/PendingIntent)
- [Runtime Permissions](https://developer.android.com/training/permissions/requesting)

### 7.2 추가 기능 아이디어

**1. 알림 커스터마이징**
- Custom Layout 사용
- 큰 이미지 표시 (BigPictureStyle)
- 진행률 바 표시 (ProgressStyle)

**2. 알림 액션 버튼**
- "다시 시작", "종료" 버튼 추가
- BroadcastReceiver로 버튼 처리

**3. 소리/진동 커스터마이징**
- Custom notification sound
- 진동 패턴 변경

**4. 다크 모드 대응**
- 알림 아이콘 색상 변경
- 다크/라이트 테마별 아이콘

---

## 8. 정리

### 우리가 배운 것

1. **Android Notification 시스템**
   - NotificationChannel (Android 8.0+)
   - NotificationCompat.Builder
   - NotificationManager

2. **PendingIntent**
   - 개념과 필요성
   - FLAG_IMMUTABLE (Android 12+)
   - getActivity()로 앱 실행

3. **Android 권한**
   - Runtime Permission
   - POST_NOTIFICATIONS (Android 13+)
   - ActivityResultContracts.RequestPermission()

4. **예외 처리 및 권한 체크**
   - runCatching으로 안전한 알림 표시
   - 권한 체크로 크래시 방지
   - 로그로 디버깅 용이
---

## 부록: 전체 코드 요약

### A. 파일 구조

```
app/src/main/java/com/example/kuit6_notification/
├── MainActivity.kt
├── model/
│   └── TimerState.kt
├── ui/
│   ├── components/
│   ├── screen/
│   │   └── TimerScreen.kt            ← 수정
│   └── theme/
├── util/
│   ├── NotificationHelper.kt         ← 추가 (상수 포함)
│   └── TimeFormatter.kt
└── viewmodel/
    └── TimerViewModel.kt             ← 수정
```

### B. 핵심 클래스 관계도

```
MainActivity
    │
    └─ TimerScreen (권한 요청)
           │
           └─ TimerViewModel
                  │
                  └─→ NotificationHelper
                          │
                          ├─→ 권한 체크
                          ├─→ 예외 처리
                          └─→ 알림 표시 → PendingIntent → MainActivity
```

---

## 고급: Foreground Service로 리팩토링

### 왜 Foreground Service가 필요한가?

현재 구현의 **치명적인 문제점**:

```
사용자가 타이머 시작
  ↓
홈 버튼 누름 (앱 백그라운드로 이동)
  ↓
타이머가 멈춤! 💀
  ↓
알림이 표시되지 않음
```

**원인**: ViewModel은 Activity의 생명주기에 종속되어 있음
- 앱이 백그라운드로 가면 Activity가 파괴될 수 있음
- ViewModel의 코루틴도 함께 취소됨

**해결책**: Foreground Service 사용
- 시스템이 강제 종료하지 않음
- 백그라운드에서도 계속 실행됨
- 지속적인 알림 표시 (사용자가 인지 가능)

---

### Foreground Service vs Background Service

| 구분 | Background Service | Foreground Service |
|------|-------------------|-------------------|
| **Android 8.0+ 제한** | 몇 분 안에 종료됨 | 종료되지 않음 |
| **알림 표시** | 선택 사항 | **필수** (없으면 종료) |
| **사용 사례** | 짧은 작업 (파일 업로드) | 장시간 작업 (음악 재생, 타이머) |
| **배터리 영향** | 낮음 (금방 종료) | 높음 (계속 실행) |
| **권한** | 없음 | FOREGROUND_SERVICE (14+) |

---

### 리팩토링 계획

**변경 사항 요약**:

```
[기존] ViewModel이 타이머 관리
  ↓
[변경] TimerService가 타이머 관리
       ViewModel은 Service 제어만 담당
```

**새로운 아키텍처**:

```
TimerScreen
    │
    └─→ TimerViewModel
           │
           └─→ TimerService (Foreground)
                  │
                  ├─→ 지속 알림 (진행 중)
                  └─→ 완료 알림 (완료 시)
```

---

### Step 1: TimerService.kt 생성

**목적**: 백그라운드에서 타이머를 실행하는 Foreground Service

**경로**: `app/src/main/java/com/example/kuit6_notification/service/TimerService.kt`

```kotlin
package com.example.kuit6_notification.service

import android.app.Service
import android.content.Intent
import android.os.Binder
import android.os.CountDownTimer
import android.os.IBinder
import android.util.Log
import com.example.kuit6_notification.util.NotificationHelper
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow

class TimerService : Service() {

    private val binder = TimerBinder()
    private var countDownTimer: CountDownTimer? = null
    private lateinit var notificationHelper: NotificationHelper

    // 타이머 상태를 외부에 공유
    private val _remainingMillis = MutableStateFlow(0L)
    val remainingMillis: StateFlow<Long> = _remainingMillis

    private val _isRunning = MutableStateFlow(false)
    val isRunning: StateFlow<Boolean> = _isRunning

    companion object {
        const val ACTION_START_TIMER = "ACTION_START_TIMER"
        const val ACTION_PAUSE_TIMER = "ACTION_PAUSE_TIMER"
        const val ACTION_STOP_TIMER = "ACTION_STOP_TIMER"
        const val EXTRA_DURATION_MILLIS = "EXTRA_DURATION_MILLIS"

        private const val FOREGROUND_NOTIFICATION_ID = 1000
    }

    override fun onCreate() {
        super.onCreate()
        notificationHelper = NotificationHelper(this)
        Log.d("TimerService", "Service 생성됨")
    }

    override fun onStartCommand(intent: Intent?, flags: Int, startId: Int): Int {
        when (intent?.action) {
            ACTION_START_TIMER -> {
                val durationMillis = intent.getLongExtra(EXTRA_DURATION_MILLIS, 0L)
                startTimer(durationMillis)
            }
            ACTION_PAUSE_TIMER -> pauseTimer()
            ACTION_STOP_TIMER -> stopTimer()
        }
        return START_STICKY  // 시스템에 의해 종료되면 재시작
    }

    override fun onBind(intent: Intent): IBinder = binder

    /**
     * 타이머 시작
     */
    private fun startTimer(durationMillis: Long) {
        // Foreground Service로 승격 (알림 필수!)
        val notification = notificationHelper.createForegroundNotification(
            durationMillis / 1000
        )
        startForeground(FOREGROUND_NOTIFICATION_ID, notification)

        _remainingMillis.value = durationMillis
        _isRunning.value = true

        countDownTimer?.cancel()
        countDownTimer = object : CountDownTimer(durationMillis, 50L) {
            override fun onTick(millisUntilFinished: Long) {
                _remainingMillis.value = millisUntilFinished

                // 1초마다 알림 업데이트 (너무 자주 하면 배터리 소모)
                if (millisUntilFinished % 1000 < 100) {
                    updateForegroundNotification(millisUntilFinished)
                }
            }

            override fun onFinish() {
                _remainingMillis.value = 0L
                _isRunning.value = false

                // 완료 알림 표시
                notificationHelper.showCompletedNotification()

                // Foreground 상태 해제
                stopForeground(STOP_FOREGROUND_REMOVE)
                stopSelf()  // Service 종료

                Log.d("TimerService", "타이머 완료")
            }
        }.start()

        Log.d("TimerService", "타이머 시작: ${durationMillis}ms")
    }

    /**
     * 타이머 일시정지
     */
    private fun pauseTimer() {
        countDownTimer?.cancel()
        _isRunning.value = false
        Log.d("TimerService", "타이머 일시정지")
    }

    /**
     * 타이머 중지
     */
    private fun stopTimer() {
        countDownTimer?.cancel()
        _remainingMillis.value = 0L
        _isRunning.value = false

        stopForeground(STOP_FOREGROUND_REMOVE)
        stopSelf()

        Log.d("TimerService", "타이머 중지")
    }

    /**
     * Foreground 알림 업데이트
     */
    private fun updateForegroundNotification(remainingMillis: Long) {
        val notification = notificationHelper.createForegroundNotification(
            remainingMillis / 1000
        )
        notificationHelper.updateNotification(FOREGROUND_NOTIFICATION_ID, notification)
    }

    override fun onDestroy() {
        super.onDestroy()
        countDownTimer?.cancel()
        Log.d("TimerService", "Service 종료됨")
    }

    /**
     * Service와 Activity를 연결하는 Binder
     */
    inner class TimerBinder : Binder() {
        fun getService(): TimerService = this@TimerService
    }
}
```

#### 코드 설명

**1. startForeground() - 핵심!**
```kotlin
startForeground(FOREGROUND_NOTIFICATION_ID, notification)
```
- Service를 Foreground로 승격
- 알림이 반드시 표시되어야 함
- 이 호출 없이는 Android 8.0+에서 5초 후 크래시

**2. CountDownTimer 사용**
```kotlin
object : CountDownTimer(durationMillis, 50L) {
    override fun onTick(millisUntilFinished: Long) { }
    override fun onFinish() { }
}
```
- 코루틴 대신 CountDownTimer 사용
- Service는 생명주기가 다르므로 CountDownTimer가 더 적합

**3. StateFlow로 상태 공유**
```kotlin
private val _remainingMillis = MutableStateFlow(0L)
val remainingMillis: StateFlow<Long> = _remainingMillis
```
- ViewModel이 Service의 상태를 구독 가능
- UI 업데이트에 사용

**4. START_STICKY**
```kotlin
return START_STICKY
```
- 시스템에 의해 종료되면 자동 재시작
- 단, Intent는 null로 전달됨

---

### Step 2: NotificationHelper.kt 수정

**목적**: Foreground Service용 알림 생성 함수 추가

**경로**: `app/src/main/java/com/example/kuit6_notification/util/NotificationHelper.kt`

기존 파일에 **다음 함수들을 추가**합니다:

```kotlin
/**
 * Foreground Service용 진행 중 알림 생성
 */
fun createForegroundNotification(remainingSeconds: Long): Notification {
    val minutes = remainingSeconds / 60
    val seconds = remainingSeconds % 60
    val timeText = String.format("%02d:%02d", minutes, seconds)

    return NotificationCompat.Builder(context, NOTIFICATION_CHANNEL_ID)
        .setContentTitle("타이머 실행 중")
        .setContentText("남은 시간: $timeText")
        .setSmallIcon(R.drawable.ic_launcher_foreground)
        .setContentIntent(createContentIntent())
        .setOngoing(true)  // 스와이프로 제거 불가
        .setPriority(NotificationCompat.PRIORITY_LOW)  // 조용한 알림
        .setSound(null)  // 소리 없음
        .build()
}

/**
 * 알림 업데이트 (Foreground Service용)
 */
fun updateNotification(notificationId: Int, notification: Notification) {
    runCatching {
        notificationManager.notify(notificationId, notification)
    }.onFailure { e ->
        Log.e("NotificationHelper", "알림 업데이트 중 예외 발생", e)
    }
}
```

#### 코드 설명

**setOngoing(true)**
```kotlin
.setOngoing(true)
```
- 사용자가 스와이프로 제거할 수 없음
- Foreground Service는 알림이 필수이므로 제거 방지

**PRIORITY_LOW + setSound(null)**
```kotlin
.setPriority(NotificationCompat.PRIORITY_LOW)
.setSound(null)
```
- 진행 중 알림은 조용하게 (소리/진동 없음)
- 완료 알림만 소리/진동

---

### Step 3: AndroidManifest.xml 수정

**목적**: Service 등록 및 권한 추가

**경로**: `app/src/main/AndroidManifest.xml`

#### 3.1 권한 추가

```xml
<!-- 기존 권한 -->
<uses-permission android:name="android.permission.POST_NOTIFICATIONS" />

<!-- Foreground Service 권한 추가 (Android 9+) -->
<uses-permission android:name="android.permission.FOREGROUND_SERVICE" />

<!-- Android 14+용 세부 권한 (선택 사항, 타이머 등 특수 용도) -->
<uses-permission android:name="android.permission.FOREGROUND_SERVICE_SPECIAL_USE" />
```

#### 3.2 Service 등록

```xml
<application
    ...>

    <activity
        android:name=".MainActivity"
        ...>
    </activity>

    <!-- TimerService 등록 -->
    <service
        android:name=".service.TimerService"
        android:enabled="true"
        android:exported="false"
        android:foregroundServiceType="specialUse">
        <property
            android:name="android.app.PROPERTY_SPECIAL_USE_FGS_SUBTYPE"
            android:value="timer" />
    </service>

</application>
```

#### 코드 설명

**android:exported="false"**
- 다른 앱에서 이 Service를 시작할 수 없음 (보안)

**android:foregroundServiceType="specialUse"**
- Android 14+ 필수
- 타이머는 특수 용도로 분류됨
- 다른 타입: `mediaPlayback`, `location`, `camera` 등

---

### Step 4: TimerViewModel.kt 리팩토링

**목적**: Service 제어로 변경

**경로**: `app/src/main/java/com/example/kuit6_notification/viewmodel/TimerViewModel.kt`

#### 4.1 전체 코드 (리팩토링 버전)

```kotlin
package com.example.kuit6_notification.viewmodel

import android.app.Application
import android.content.ComponentName
import android.content.Context
import android.content.Intent
import android.content.ServiceConnection
import android.os.IBinder
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.viewModelScope
import com.example.kuit6_notification.model.TimerState
import com.example.kuit6_notification.service.TimerService
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch

class TimerViewModel(application: Application) : AndroidViewModel(application) {

    private val context = application.applicationContext

    // Service 연결
    private var timerService: TimerService? = null
    private var isBound = false

    private val serviceConnection = object : ServiceConnection {
        override fun onServiceConnected(name: ComponentName?, service: IBinder?) {
            val binder = service as TimerService.TimerBinder
            timerService = binder.getService()
            isBound = true

            // Service의 상태를 구독
            viewModelScope.launch {
                timerService?.remainingMillis?.collect { millis ->
                    updateTimerState(millis)
                }
            }
        }

        override fun onServiceDisconnected(name: ComponentName?) {
            timerService = null
            isBound = false
        }
    }

    private val _timerState = MutableStateFlow<TimerState>(TimerState.Idle)
    val timerState: StateFlow<TimerState> = _timerState

    private val _hours = MutableStateFlow(0)
    val hours: StateFlow<Int> = _hours

    private val _minutes = MutableStateFlow(0)
    val minutes: StateFlow<Int> = _minutes

    private val _seconds = MutableStateFlow(10)
    val seconds: StateFlow<Int> = _seconds

    init {
        // Service에 바인드
        bindToService()
    }

    private fun bindToService() {
        val intent = Intent(context, TimerService::class.java)
        context.bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE)
    }

    fun setHours(value: Int) {
        _hours.value = value.coerceIn(0, 23)
    }

    fun setMinutes(value: Int) {
        _minutes.value = value.coerceIn(0, 59)
    }

    fun setSeconds(value: Int) {
        _seconds.value = value.coerceIn(0, 59)
    }

    /**
     * 타이머 시작 - Service에 위임
     */
    fun startTimer() {
        val totalMillis = calculateTotalMillis()
        if (totalMillis <= 0) return

        val intent = Intent(context, TimerService::class.java).apply {
            action = TimerService.ACTION_START_TIMER
            putExtra(TimerService.EXTRA_DURATION_MILLIS, totalMillis)
        }
        context.startForegroundService(intent)  // Foreground Service 시작

        _timerState.value = TimerState.Running(totalMillis)
    }

    /**
     * 타이머 일시정지 - Service에 위임
     */
    fun pauseTimer() {
        val intent = Intent(context, TimerService::class.java).apply {
            action = TimerService.ACTION_PAUSE_TIMER
        }
        context.startService(intent)

        _timerState.value = TimerState.Paused(timerService?.remainingMillis?.value ?: 0L)
    }

    /**
     * 타이머 리셋 - Service에 위임
     */
    fun resetTimer() {
        val intent = Intent(context, TimerService::class.java).apply {
            action = TimerService.ACTION_STOP_TIMER
        }
        context.startService(intent)

        _timerState.value = TimerState.Idle
    }

    /**
     * Service의 상태를 TimerState로 변환
     */
    private fun updateTimerState(remainingMillis: Long) {
        _timerState.value = when {
            remainingMillis <= 0 -> TimerState.Completed
            timerService?.isRunning?.value == true -> TimerState.Running(remainingMillis)
            else -> TimerState.Paused(remainingMillis)
        }
    }

    private fun calculateTotalMillis(): Long {
        return ((_hours.value * 3600L) + (_minutes.value * 60L) + _seconds.value) * 1000L
    }

    override fun onCleared() {
        super.onCleared()
        if (isBound) {
            context.unbindService(serviceConnection)
            isBound = false
        }
    }
}
```

#### 코드 설명

**1. startForegroundService() - Android 8.0+ 필수**
```kotlin
context.startForegroundService(intent)
```
- `startService()` 대신 `startForegroundService()` 사용
- Android 8.0+에서 필수
- 5초 안에 `startForeground()` 호출 안 하면 크래시

**2. ServiceConnection으로 양방향 통신**
```kotlin
private val serviceConnection = object : ServiceConnection {
    override fun onServiceConnected(name: ComponentName?, service: IBinder?) {
        // Service의 StateFlow를 구독
        timerService?.remainingMillis?.collect { }
    }
}
```
- Service의 실시간 상태를 ViewModel이 수신
- UI 업데이트에 사용

**3. bindService() vs startService()**
```kotlin
// bind: Service와 통신 (StateFlow 구독)
context.bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE)

// start: Service에 명령 전달 (Action)
context.startForegroundService(intent)
```
- 둘 다 사용하는 이유: 통신 + 명령 전달

---

**결론**: 타이머 앱처럼 백그라운드 동작이 필수인 경우 Foreground Service는 **선택이 아닌 필수**입니다.

---

## 마치며

이 가이드를 통해 Android 알림 시스템의 핵심 개념과 **안전한 구현 방법**을 이해하셨기를 바랍니다.

**핵심 포인트**
- Android 알림은 **NotificationChannel** (8.0+)이 필수
- 시스템이 앱을 대신 실행하려면 **PendingIntent** 필요
- Android 13+는 **POST_NOTIFICATIONS** 권한 필요
- **권한 체크 + 예외 처리**로 안전한 알림 구현
- **상수는 사용하는 클래스 내부**에 두면 응집도 증가

**간단하지만 안전한 구현**
- 액션 버튼 없이 기본 알림만 구현
- 권한 체크로 크래시 방지
- 예외 처리로 안정성 확보
- 초보자도 이해 가능하지만 프로덕션에서도 사용 가능

질문이나 피드백은 언제든 환영합니다!

---

**작성일**: 2025년
**작성자**: Android 개발 강의 자료
**버전**: 3.0 (Safe & Clean)
